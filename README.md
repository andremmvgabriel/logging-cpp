- [I. Introduction](#i-introduction)
- [II. Platforms](#ii-platforms)
- [III. How to use it + usage samples](#iii-how-to-use-it--usage-samples)
  - [1. Initiate the logger](#1-initiate-the-logger)
  - [2. Logger settings](#2-logger-settings)
  - [3. Basic logs](#3-basic-logs)
  - [4. Timestamps](#4-timestamps)
  - [5. Log print: One line Vs Multiple lines](#5-log-print-one-line-vs-multiple-lines)
  - [6. Maximum log file size](#6-maximum-log-file-size)
  - [7. Header and sub-header log options](#7-header-and-sub-header-log-options)

----------------------

# I. Introduction

This Logger is very simple and easy to be used. 

# II. Platforms

Currently, the Logger can only be used in Linux platforms.

# III. How to use it + usage samples

## 1. Initiate the logger

To initiate the logger, you only need to create the object and use the init function, as such:

``` cpp
#include "logging.hpp"

int main() {
    // Creates the logger object
    gabe::logging::Logger logger;

    // Initiates the logger
    logger.init();
}
```

## 2. Logger settings

The logger has 7 settings parameters that can be set by the user:

1. The directory to save the logs in;
2. The name of the logs files;
3. The maximum size of a log file;
4. The maximum line size inside the logs;
5. Allowence to print a log line into multiple lines (if reaches maximum parameter in 4.);
6. Template of the timestamp;
7. Template of Severity.

By default, these assume the following values:

``` cpp
{
    "logs/",                        // Logs directory
    "log_file",                     // Logs base file name
    5000000,                        // Max file size (in bytes)
    -1,                             // Max line size - (no max size / "infinite" characters)
    true,                           // Allow logs for multiple lines
    opts::TimestampTemplate::TIME,  // Time only timestamp
    opts::LogTemplate::SEV_MSG,     // Log as Severity + Message
};
```

If the user desires to change a setting, it should be done before initiating the logger. These settings can be changed individually, or all at once if preferred. The following code shows how to do both:

``` cpp
#include "logging.hpp"

// You can make typedefs to make your life easier
typedef gabe::logging::Logger Logger;
typedef gabe::logging::opts::LogTemplate LogTemplate;
typedef gabe::logging::opts::TimestampTemplate TimeTemplate;

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
        TimeTemplate::TIME,
        LogTemplate::TIME_SEV_MSG
    });

    // Initiates the logger
    logger.init();
}
```

***Note:*** Currently if you want to change a specific setting, you will have to insert the default values of all the others settings on the creation of the Logger object. However, it is planned to implement a setting change methodology to change individually each one. But for now, you will have to use as it is... Sorry about that :/

## 3. Basic logs

To write a log, the user only has to call the write_log function, as following:

``` cpp
#include "logging.hpp"

// You can make typedefs to make your life easier
typedef gabe::logging::Logger Logger;
typedef gabe::logging::Severity logSev;

int main() {
    // Creates the logger object
    Logger logger;

    // Initiates the logger
    logger.init();

    // Writes a log
    logger.write_log( logSev::INFO, "My first log example." );
}
```

***Output:***

``` txt
[ info  ] My first log example.                                                                               
```

As can be seen in the example, to be able to use the write_log function, a severity level as to be specified as well as the log message. Since the logger is using the default settings, the output is the most basic log, which is defined by the severity level, in brackets, followed by the message.

There are several severity levels that can be specified for logging:

``` cpp
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

***Output:***

```
[ trace ] This is a TRACE log.                         
[ info  ] This is a INFO log.                          
[ debug ] This is a DEBUG log.                         
[warning] This is a WARNING log.                       
[ error ] This is a ERROR log.                         
[ fatal ] This is a FATAL log.   
```

## 4. Timestamps

If it is important to have a timestamp attached with each printed log, the first that has to be done is to change the log template and allow the timestamp to be printed. There are four log templates available to be choose:

```
enum class LogTemplate
{
    SEV_MSG         = 0,    // [Severity] Message
    TIME_SEV_MSG    = 1,    // [Timestamp][Severity] Message
    SEV_TIME_MSG    = 2,    // [Severity][Timestamp] Message
    SEV_MSG_TIME    = 4     // [Severity] Message [Timestamp]
};
```

The ***SEV_MSG*** is the default setting, which does not allow to print any timestamp. However, and as can be seen above, the user has the option to have the timestamp on the left of the severity (***TIME_SEV_MSG***), on the right of the severity (***SEV_TIME_MSG***), or on the end of the log (***SEV_MSG_TIME***), as shown in the outputs below, respectively.

```                                    
[ info  ] Log without timestamp.

[11:48:13][ info  ] Timestamp on the left of the severity level.

[ info  ][11:48:13] Timestamp on the right of the severity level.

[ info  ] Timestamp on the end of the log. [11:48:13]
```

In addition to the timestamps, the user has also three options to choose from, as can be seen below (time is the only thing printed in the timestamp by default).

```
enum class TimestampTemplate
{
    TIME,                   // [hh:mm::ss]
    CALENDAR_TIME,          // [Week Month Day][hh::mm::ss]
    CALENDAR_YEAR_TIME,     // [Week Month Day Year][hh::mm::ss]
};
```

***Output:***

```
[09:28:28][ info  ] Only time in the timestamp.

[Thu Feb 25][09:28:28][ info  ] Calendar and time in the timestamp.

[Thu Feb 25 2021][09:28:28][ info  ] Calendar, year, and time in the timestamp.
```

## 5. Log print: One line Vs Multiple lines

This feature is mainly a customization preference for the user, and it is defined by the setting ***MULTIPLE_LINES***, which, by default, is set as true. The behaviour of this feature is also dependent of the setting ***LINE_SIZE***. Basically, if the user log message is bigger than the maximum size of the line, it will insert a '(...)' at the end of the log, and the just the beggining of the specified message will be printed. The following output shows the behaviour of the multiple lines setting as off and on, respectively, for a maximum line size of 50 characters and for the same log message.

```
[ info  ] This log has 95 characters. It is intended t (...) [10:02:08]

[ info  ] This log has 95 characters. It is intended to show [10:02:08]
[ info  ] the behaviour of the MULTIPLE LINES setting.       [10:02:08]
```

## 6. Maximum log file size

The maximum file size is defined by the setting ***FILE_SIZE***. If at a certain point the log file reaches the maximum size, it will safely close the file and open a new one, without overwriting the previous one. 

**Note:** if at some instance a log file has, for example, only 50 bytes left to reach the maximum file size, and the log message has 200 bytes, don't worry, the log will not be split into the two log files. It will write the whole message in the current log file, and then proceed to open a new file for future logs.

## 7. Header and sub-header log options

Last but not least, the headers and the sub-headers. Lets think of the headers and sub-headers as two properties of the log in order to make the whole file more easy to read and identify wanted logs. All the log prints shown before are the default prints that are printed with the default calling of the write_log function. However, if the user wants to print the log as a header, he has to specify the header in the write_log function, as following:

``` cpp
// You can make typedefs to make your life easier
typedef gabe::logging::opts::TextType TextType;
typedef gabe::logging::Severity logSev;

logger.write_log<TextType::HEADER>( logSev::INFO, "This is a Header." );

/* Output:
[ info  ]                                                    [10:19:57]
[ info  ] ************************************************** [10:19:57]
[ info  ] *               This is a Header.                * [10:19:57]
[ info  ] ************************************************** [10:19:57]
*/
```

As can be seen, the header message log is surrounded by '*' characters, in order to be more easy to be identified, the text is centered, and there is an empty line printed before the header.

Now lets check the same write_log but for a sub-header:

``` cpp
// You can make typedefs to make your life easier
typedef gabe::logging::opts::TextType TextType;
typedef gabe::logging::Severity logSev;

logger.write_log<TextType::HEADER>( logSev::INFO, "This is a Header." );

/* Output:
[ info  ] ~~~           This is a Sub-Header.            ~~~ [10:22:41]
*/
```

The sub-header is as well centered, but it only identified in the beginning and the end of the message by three '~' characters, and it does not has any empty log line before as the header does.

**Note:** This two properties are also affected by the maximum line size and the multiple lines defined in the section **5**. The following examples show the header and sub-header for those cases:

```
[ info  ]                                                    [10:30:11]
[ info  ] ************************************************** [10:30:11]
[ info  ] * This is a huge Header. This is a huge He (...) * [10:30:11]
[ info  ] ************************************************** [10:30:11]

[ info  ]                                                    [10:30:11]
[ info  ] ************************************************** [10:30:11]
[ info  ] * This is a huge Header. This is a huge Header.  * [10:30:11]
[ info  ] * This is a huge Header. This is a huge Header.  * [10:30:11]
[ info  ] ************************************************** [10:30:11]



[ info  ] ~~~ This is a huge Sub-Header. This is a (...) ~~~ [10:30:11]

[ info  ] ~~~ This is a huge Sub-Header. This is a huge  ~~~ [10:30:11]
[ info  ] ~~~ Sub-Header. This is a huge Sub-Header. Thi ~~~ [10:30:11]
[ info  ] ~~~          s is a huge Sub-Header.           ~~~ [10:30:11]
```



