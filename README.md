# Logger

This Logger has multiple features implemented that can be defined by the user

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
