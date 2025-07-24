#include <iostream>
#include "sms_sender.cpp"
class TestableSmsSender : public SmsSender {
public:
    void send(Schedule* schedule) override {
        std::cout << "�׽�Ʈ��SmsSender class��send�޼�������\n";
        sendMethodIsCalled = true;
    }
    bool isSendMethodIsCalled() {
        return sendMethodIsCalled;
    }
private:
    bool sendMethodIsCalled;
};