/* #include "TextUtils.hpp"

void TextUtils::Alignment::left(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        for (int i = 0; i < final_size; i++) {
            msg.push_back(' ');
        }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::right(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        std::string decoy;
        for (int i = 0; i < final_size; i++) {
            decoy.push_back(' ');
        }
        msg.insert(msg.begin(), decoy.begin(), decoy.end());
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::center(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int decoy1_size = (width - msg.size())/2;
        int decoy2_size = width - msg.size() - decoy1_size;
        std::string decoy1;
        for (int i = 0; i < decoy1_size; i++) { decoy1.push_back(' '); }
        msg.insert(msg.begin(), decoy1.begin(), decoy1.end());
        for (int i = 0; i < decoy2_size; i++) { msg.push_back(' '); }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::justify(std::string &msg, const int width) {

}
 */