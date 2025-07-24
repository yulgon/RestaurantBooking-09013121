#include "gmock/gmock.h"
#include "mail_sender.cpp"

class TestableMailSender : public MailSender {
public:
    MOCK_METHOD(void, sendMail, (Schedule*), (override));
    /*
    void sendMail(Schedule* schedule) override {
        countSendMailMethodIsCalled++;
    }
    int getCountSendMailMethodIsCalled() {
        return countSendMailMethodIsCalled;
    }
private:
    int countSendMailMethodIsCalled = 0;
    */
};