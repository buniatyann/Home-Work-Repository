#include "sha.hpp"

std::string sha256::hash(const std::string& hash) {
    std::vector<uint8_t> data(hash.begin(), hash.end());
    uint64_t bit_length = hash.size() * 8;

    // padding 
    data.push_back(0x80);
    while (data.size() % 64 != 56) {
        data.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        data.push_back((bit_length >> (i * 8)) & 0xFF);
    }

    // 512bit block processing
    for (std::size_t i =0; i < data.size(); i += 64) {
        process_block(data.data() + i);
    }

    // hash to hex string
    std::stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << std::setw(8) << std::setfill('0') << h[i];
    }

    // reset hash for next use
    h[0] = 0x6a09e667; 
    h[1] = 0xbb67ae85; 
    h[2] = 0x3c6ef372; 
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f; 
    h[5] = 0x9b05688c; 
    h[6] = 0x1f83d9ab; 
    h[7] = 0x5be0cd19;

    return ss.str();
}

uint32_t sha256::rotr(uint32_t x, uint32_t n)
{
    return (x >> n) | (x << (32 - n));
}

uint32_t sha256::ch(uint32_t x, uint32_t y, int32_t z) {
    return (x & y) ^ (~x & z); 
}

uint32_t sha256::maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sha256::sigma0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

uint32_t sha256::sigma1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

uint32_t sha256::gamma0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 13) ^ (x >> 3); 
}

uint32_t sha256::gamma1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

void sha256::process_block(const uint8_t *block) {
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h, t1, t2;

    // message schedule initialization
    for (int i = 0; i < 16; ++i) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
               (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    for (int i = 16; i < 64; ++i) {
        w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];
    }

    // working variables initialization
    a = this->h[0];
    b = this->h[1];
    c = this->h[2];
    d = this->h[3];
    e = this->h[4];
    f = this->h[5];
    g = this->h[6];
    h = this->h[7];

    for (int i = 0; i < 64; ++i) {
        t1 = h + sigma1(e) + ch(e, f, g) + K[i] + w[i];
        t2 = sigma0(a) + maj(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    // update hash values
    this->h[0] += a; this->h[1] += b; this->h[2] += c; this->h[3] += d;
    this->h[4] += e; this->h[5] += f; this->h[6] += g; this->h[7] += h;
}
