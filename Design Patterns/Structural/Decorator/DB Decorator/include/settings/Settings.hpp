#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace settings {
    constexpr unsigned RATE_LIMIT          = 10;
    constexpr unsigned TIME_WINDOW_SECONDS = 60;
    constexpr const char* LOG_FILE         = "db.log";
    constexpr const char* AUDIT_FILE       = "db_audit.log";
} // namespace settings

#endif // SETTINGS_HPP