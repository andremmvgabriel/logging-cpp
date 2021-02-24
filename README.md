# Logger

This Logger is very simple and easy to be used. 

## Platforms

-------------

Currently, the Logger can only be used in Linux platforms.

## How to use it + usage samples

--------------

#### 1. Initiate the logger



To initiate the logger, you only need to create the object and use the init function, as such:

```
#include "Logger.hpp"

int main() {
    // Creates the logger object
    Logging::Logger logger;

    // Initiates the logger
    logger.init();
}
```

#### 2. Logger settings

The logger has 7 settings parameters that can be set by the user. These settings are defined in the following enumerator:

```
enum class Setting
{
    LOGS_DIRECTORY,         // Directory to save logs
    FILE_NAME,              // Base name of the logs
    FILE_SIZE,              // Size of the log files
    LINE_SIZE,              // Size of each log line
    ALLOW_MULTIPLE_LINES,   // Allow a log to fill multiple lines
    TIME_TEMPLATE,          // Template of the timestamp
    LOG_TEMPLATE            // Template of the log
};
```

By default, these assume the following values:

```
{
    "logs/",                        // Logs directory
    "log_file",                     // Logs base file name
    5000000,                        // Max file size (in bytes)
    66,                             // Max line size - 66 characters
    true,                           // Allow logs for multiple lines
    Edit::TimestampTemplate::NONE,  // No timestamp
    Edit::LogTemplate::SEV_MSG,     // Log as Severity + Message
};
```

If the user desires to change a setting, it should be done before initiating the logger. These settings can be changed individually, or all at once if preferred. The following code shows how to do both:

```
#include "Logger.hpp"

int main() {
    // Creates the logger object
    Logging::Logger logger;

    // Change all the settings
    logger.setSettings({
        "my_other_directory/",
        "my_log_file_name",
        1000000000000,
        100,
        false,
        Logging::Edit::TimestampTemplate::TIME,
        Logging::Edit::LogTemplate::TIME_SEV_MSG
    });

    // Change a specific setting
    logger.setSetting(
        Logging::Edit::Setting::FILE_SIZE,
        123456789
    );

    // Initiates the logger
    logger.init();
}
```

#### 3. Basic logs

To write a log, the user only has to call the write_log function, as following:

```
#include "Logger.hpp"

int main() {
    // Creates the logger object
    Logging::Logger logger;

    // Initiates the logger
    logger.init();

    // Writes a log
    logger.write_log( Logging::Severity::INFO, "My first log example." );
}
```
***Output:***
>[ info  ] My first log example.                                                                               

As can be seen, the most basic log is defined








There are several severity levels that can be defined everytime the function to write the log is called:

```
enum class Severity
{
    TRACE   = 1,
    DEBUG   = 2,
    INFO    = 4,
    WARNING = 8,
    ERROR   = 16,
    FATAL   = 32
};
```

The following section shows the most basic log for each one of the severity levels:

```
[ trace ] This is a TRACE log.                         
[ info  ] This is a INFO log.                          
[ debug ] This is a DEBUG log.                         
[warning] This is a WARNING log.                       
[ error ] This is a ERROR log.                         
[ fatal ] This is a FATAL log.   
```

If it is important to have a timestamp attached with each printed log, there are some options that the user can define. By default, the timestamp is set to NONE.

```
enum class TimestampTemplate
{
    NONE,                   // No timestamp
    TIME,                   // [hh:mm::ss]
    CALENDAR_TIME,          // [Week Month Day hh::mm::ss]
    CALENDAR_YEAR_TIME,     // [Week Month Day Year hh::mm::ss]
};
```

In addition, there are also templates for the log, in order to adjust the position of the timestamp:

```
enum class LogTemplate
{
    SEV_MSG         = 0,    // [Severity] Message
    TIME_SEV_MSG    = 1,    // [Timestamp][Severity] Message
    SEV_TIME_MSG    = 2,    // [Severity][Timestamp] Message
    SEV_MSG_TIME    = 4     // [Severity] Message [Timestamp]
};
```



```
logger.setSetting(Logging::Edit::Setting::TIME_TEMPLATE, Logging::Edit::TimestampTemplate::TIME);
logger.init();
logger.write_log(Logging::Severity::INFO, "Time is now being printed.");
// Output: [11:35:53][ info  ] Time is now being printed.                                                                              

-----------------------------------------------------------------------------------------------------------

logger.setSetting(Logging::Edit::Setting::TIME_TEMPLATE, Logging::Edit::TimestampTemplate::CALENDAR_TIME);
logger.init();
logger.write_log(Logging::Severity::INFO, "Calendar + Time is now being printed.");                       
// Output: [Wed Feb 24][11:35:53][ info  ] Calendar + Time is now being printed.

-----------------------------------------------------------------------------------------------------------

logger.setSetting(Logging::Edit::Setting::TIME_TEMPLATE, Logging::Edit::TimestampTemplate::CALENDAR_YEAR_TIME);
logger.init();
logger.write_log(Logging::Severity::INFO, "Calendar + Year + Time is now being printed.");        
// Output: [Wed Feb 24 2021][11:35:53][ info  ] Calendar + Year + Time is now being printed.        
```

The place where the time is displayed is also customizable. These are the templates of the log, and the options are:

```
enum class LogTemplate
{
    SEV_MSG         = 0,    // [Severity] Message
    TIME_SEV_MSG    = 1,    // [Timestamp][Severity] Message
    SEV_TIME_MSG    = 2,    // [Severity][Timestamp] Message
    SEV_MSG_TIME    = 4     // [Severity] Message [Timestamp]
};
```

```                                    
[ info  ] Log without timestamp.                                                                              
                                                                                                                                
[11:48:13][ info  ] Timestamp on the left of the severity level.                                                        
                                                                                                                      
[ info  ][11:48:13] Timestamp on the right of the severity level.                                                       
                                                                                                   
[ info  ] Timestamp on the end of the log. [11:48:13]
```
