#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "schedule.cpp"
#include "mail_sender.cpp"
#include "sms_sender.cpp"

using std::vector;

class BookingScheduler {
public:
    BookingScheduler(int capacityPerHour) :
        capacityPerHour{ capacityPerHour } {
        smsSender = new SmsSender();
        mailSender = new MailSender();
    }

    void addSchedule(Schedule* schedule) {

        // ������ �������� ���� ��� RuntimeException �߻�
        if (schedule->getDateTime().tm_min != 0) {
            throw std::runtime_error("Booking should be on the hour.");
        }

        // �ð��� �����ο��� �ʰ��� ��� RuntimeException �߻�
        int numberOfPeople = schedule->getNumberOfPeople();
        for (Schedule* bookedSchedule : schedules) {
            if (isSameTime(bookedSchedule->getDateTime(), schedule->getDateTime())) {
                numberOfPeople += bookedSchedule->getNumberOfPeople();
            }
        }
        if (numberOfPeople > capacityPerHour) {
            throw std::runtime_error("Number of people is over restaurant capacity per hour");
        }

        /*
        // �Ͽ��Ͽ��� �ý����� �������� �ʴ´�.
        time_t now = time(nullptr);
        if (getDayOfWeek(now) == "Sunday") {
            throw std::runtime_error("Booking system is not available on sunday");
        }
        */

        schedules.push_back(schedule);

        // ������ SMS �߼�
        smsSender->send(schedule);
        // ���� E-Mail�� ������ ���� ��� E-Mail �߼�
        if (schedule->getCustomer().getEmail() != "") {
            mailSender->sendMail(schedule);
        }
    }

    bool hasSchedule(Schedule* schedule) {
        //check if an element exists in array
        return std::find(schedules.begin(), schedules.end(), schedule) != schedules.end();
    }

    void setSmsSender(SmsSender* smsSender) {
        this->smsSender = smsSender;
    }

    void setMailSender(MailSender* mailSender) {
        this->mailSender = mailSender;
    }

private:
    //�� �ð��� ������ Ȯ��
    bool isSameTime(tm a, tm b) {
        return mktime(&a) == mktime(&b);
    }

    //������ �˷��ִ� �Լ�
    string getDayOfWeek(time_t tm_t) {
        tm tmTime;
        localtime_s(&tmTime, &tm_t);
        char buffer[100] = { 0 };
        std::strftime(buffer, sizeof(buffer), "%A", &tmTime);
        return string{ buffer };
    }

    int capacityPerHour;
    vector<Schedule*> schedules;
    SmsSender* smsSender;
    MailSender* mailSender;
};