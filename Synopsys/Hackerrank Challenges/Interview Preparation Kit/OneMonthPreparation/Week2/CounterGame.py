"""
    Time O(log(n))
    Space O(log(n))
"""
def counterGame(n):
    # Convert the number n to its binary representation and remove the '0b' prefix
    n = bin(n)[2:]
    
    # Split the binary string by '1'. This creates a list of blocks of '0's.
    # For example, for n = 6 (binary "110"), the split result will be ['', '00', '']
    n = n.split('1')  # Split by '1' into segments of '0's
    
    # The length of the list 'n' will be the number of segments created by the split.
    # The total number of turns is determined by the total count of zeros in the binary form.
    # We calculate this by counting the total blocks of zeros, and subtracting 2.
    # Subtract 2 because the trailing empty string after the last '1' doesn't count towards the move.
    turns = len(n) + len(n[-1]) - 2
    
    # If the number of turns is odd, Louise wins (as she starts first); otherwise, Richard wins.
    # 'turns & 1' checks whether the number of turns is odd. If odd, Louise wins, else Richard wins.
    return 'Louise' if turns & 1 else 'Richard'
