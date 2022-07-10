#include <gabe/logging/logging.hpp>
#include <gabe/logging/formatters/Time.hpp>
#include <gabe/logging/formatters/Calendar.hpp>
#include <gabe/logging/formatters/MultiFormatter.hpp>

// Typedefs just to agile the accessibility of methods
typedef gabe::logging::SeverityLevel SevLvl;
typedef gabe::logging::LoggerHandler LogHdl;
typedef gabe::logging::formatters::Formatter Formatter;
typedef gabe::logging::formatters::MultiFormatter MultFormatter;
typedef gabe::logging::formatters::Time TimeF;
typedef gabe::logging::formatters::Calendar CaleF;

void using_time_formatter() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_formatters-time");

    // Creates the time formatter
    TimeF time_formatter;
    logger.add_formatter(time_formatter);

    // Set up the message format
    logger.set_log_layout("[%hour:%min:%sec,%ms]   [%sev]   %msg");

    // Log!
    logger.info("Testing time formatter.");
}

void using_calendar_formatter() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_formatters-calendar");

    // Creates the calendar formatter
    CaleF calendar_formatter;
    logger.add_formatter(calendar_formatter);

    // Set up the message format
    logger.set_log_layout("[%year/%month/%day %sweek]   [%sev]   %msg");

    // Log!
    logger.info("Testing calendar formatter.");
}

void using_time_and_calendar_formatters() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_formatters-time_calendar");

    // Creates the time formatter
    TimeF time_formatter;
    logger.add_formatter(time_formatter);

    // Creates the calendar formatter
    CaleF calendar_formatter;
    logger.add_formatter(calendar_formatter);

    // Set up the message format
    logger.set_log_layout("[%year/%month/%day %sweek]   [%hour:%min:%sec,%ms]   [%sev]   %msg");

    // Log!
    logger.info("Testing time and calendar formatters together!");
}

void using_custom_formatter() {
    // Creating a hipothetic formatter
    class MessageCounterFormatter : public Formatter
    {
    protected:
        int _counter = 0;
    
    public:
        MessageCounterFormatter() : Formatter("MessageCounterFormatter", "%ctr") {}

        virtual std::string _format() override {
            return fmt::format("{:8d}", _counter++);
        }
    };

    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_formatters-custom_formatter");

    // Creates the time formatter
    MessageCounterFormatter counter_formatter;
    logger.add_formatter(counter_formatter);

    // Set up the message format
    logger.set_log_layout("[Message %ctr]   [%sev]   %msg");

    for (int i = 0; i < 10; i++) {
        logger.info("Awesome message number {}!!", i);
    }
}

void using_custom_multiformatter() {
    // Creating a hipothetic formatter
    class FirstNameFormatter : public Formatter
    {
    protected:
        std::string _name;

    public:
        FirstNameFormatter() : Formatter("FirstNameFormatter", "%fn"), _name("Jon") {}

        FirstNameFormatter(const std::string &name) : Formatter("FirstNameFormatter", "%fn"), _name(name) {}

        virtual std::string _format() override {
            return fmt::format("{}", _name);
        }
    };

    // Creating another hipothetic formatter
    class LastNameFormatter : public Formatter
    {
    protected:
        std::string _name;

    public:
        LastNameFormatter() : Formatter("LastNameFormatter", "%ln"), _name("Doe") {}

        LastNameFormatter(const std::string &name) : Formatter("LastNameFormatter", "%ln"), _name(name) {}

        virtual std::string _format() override {
            return fmt::format("{}", _name);
        }
    };

    // Creating a hipothetic multi formatter
    class SignatureFormatter : public MultFormatter
    {
    public:
        SignatureFormatter() : MultFormatter("SignatureFormatter") {
            add_formatter( FirstNameFormatter() );
            add_formatter( LastNameFormatter() );
        }

        SignatureFormatter(const std::string &first, const std::string &last) : MultFormatter("SignatureFormatter") {
            add_formatter( FirstNameFormatter(first) );
            add_formatter( LastNameFormatter(last) );
        }
    };

    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_formatters-custom_multiformatter");

    // Creates the time formatter
    SignatureFormatter signature_formatter;
    logger.add_formatter(signature_formatter);

    // Set up the message format
    logger.set_log_layout("[%sev]   %msg - %fn %ln");

    logger.info("This formatter looks a bit dumb, but it is for example purposes.");
}

int main() {
    /*
    Overview:
        This example should cover how to use the library formatters as well as use custom Formatters created by you!
    */

    SET_DEFAULT_LOGS_DIRECTORY("logs");

    using_time_formatter();
    using_calendar_formatter();
    using_time_and_calendar_formatters();
    using_custom_formatter();
    using_custom_multiformatter();

    return 0;
}