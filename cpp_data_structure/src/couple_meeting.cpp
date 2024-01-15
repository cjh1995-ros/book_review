#include <queue>
#include <iostream>
#include <string>





struct Human
{
    std::string name;    
    bool        gender; // true: man; false: woman;
    Human(std::string n, bool g): name(n), gender(g) {}

    void show()
    {
        std::string gender_string = gender ? "남자" : "여자";
        std::cout << "이름: " << name << std::endl;
        std::cout << "성별: " << gender_string << std::endl;
    }
};





class MeetingProgram
{
private:
    std::queue<Human> q_man_;
    std::queue<Human> q_woman_;

public:
    void run()
    {
        std::cout << "미팅 주선 프로그램입니다." << std::endl;
        while(true)
        {
            // 이름
            std::string name;
            std::cout << "고객이름: ";
            std::cin >> name;

            // 성별
            std::string g;
            std::cout << "성별을 입력하시오(f or m): ";
            std::cin >> g;

            bool gender = g == "m" ? true : false;

            if (gender) q_man_.push({name, gender});
            else q_woman_.push({name, gender});

            if (!q_man_.empty() && !q_woman_.empty())
            {
                std::cout << "커플이 성사되었습니다!" << std::endl;
                Human man = q_man_.front();
                q_man_.pop();

                Human woman = q_woman_.front();
                q_woman_.pop();

                std::cout << man.name << "님과 " << woman.name << "님 "
                    << "진심으로 축하드립니다!";
            }
            else
            {
                std::cout << "아직 커플이 될 수 없습니다." << std::endl;
            }

            std::cout << "\n\n";
        }
    }
};





int main()
{
    MeetingProgram mp;

    mp.run();

    return 0;
}