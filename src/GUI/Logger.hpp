#pragma once
#include <gtkmm.h>
#include <string>

class Logger {
private:
    inline static Gtk::TextView* logView = nullptr;
    inline static std::stringstream buffer {};

public:
    static void init(Gtk::TextView* view)
    {
        logView = view;
    }

    static void log(const std::string& message)
    {
        if (logView) {
            // Get the text buffer from the TextView
            auto textBuffer = logView->get_buffer();

            // Append message to the actual text buffer
            textBuffer->insert(textBuffer->end(), message + "\n");

            // Create a named iterator for scrolling
            auto endIter = textBuffer->end(); // Store in variable first
            logView->scroll_to(endIter); // Pass the lvalue reference
        }
    }
};