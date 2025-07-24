#include <iostream>
#include "gmock/gmock.h"
#include "sms_sender.cpp"
class TestableSmsSender : public SmsSender {
public:
    MOCK_METHOD(void, send, (Schedule*), (override));
    /*
    void send(Schedule* schedule) override {
        std::cout << "�׽�Ʈ��SmsSender class��send�޼�������\n";
        sendMethodIsCalled = true;
    }
    bool isSendMethodIsCalled() {
        return sendMethodIsCalled;
    }
private:
    bool sendMethodIsCalled;
    */
};