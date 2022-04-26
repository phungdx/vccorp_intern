/**
 * Observer Design Pattern
 */

#include <iostream>
#include <list>
#include <string>

// interface của Observer
class IObserver {
 public:
  virtual ~IObserver(){};

  // Nhận thông tin update từ subject
  virtual void Update(const std::string &message_from_subject) = 0;
};

// Interface của subject
class ISubject {
 public:
  virtual ~ISubject(){};

  // thêm observer
  virtual void Attach(IObserver *observer) = 0;

  // remove observer
  virtual void Detach(IObserver *observer) = 0;

  // thông báo observer
  virtual void Notify() = 0;
};

/**
 */

class Subject : public ISubject {
private:
    // Lưu list các observer
    std::list<IObserver *> list_observer_;

    // tin nhắn update tới các observer
    std::string message_;

 public:
  virtual ~Subject() {
    std::cout << "Goodbye, I was the Subject.\n";
  }

  /**
   */
  void Attach(IObserver *observer) override {
    list_observer_.push_back(observer);
  }

  void Detach(IObserver *observer) override {
    list_observer_.remove(observer);
  }

    // tạo tin nhắn và gửi update đến observer
  void CreateMessage(std::string message = "Empty") {
    this->message_ = message; // thiết lập tin update
    Notify(); // thông báo đến observers
  }

  void Notify() override {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    HowManyObserver();
    // loop through từng observer để update tin vừa cập nhật
    while (iterator != list_observer_.end()) {
      (*iterator)->Update(message_); // nhận tin update từ subject
      ++iterator;
    }
  }

  // in ra số lượng observer
  void HowManyObserver() {
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }

  /**
   * Thông thường, subscription logic chỉ là 1 phần nhỏ của những gì subject có
   * thể làm. Subjects thường giữ 1 số thông tin quan quan trọng, mà có thể kích hoạt
   * 1 phương thức thông báo bất cứ khi nào có gì quan trọng sắp xảy ra (hoặc sau khi xảy ra).
   */
  void SomeBusinessLogic() {
    this->message_ = "change message message";
    Notify();
    std::cout << "I'm about to do some thing important\n";
  }
};


class Observer : public IObserver {

private:
  std::string message_from_subject_; // lưu tin update từ subject
  Subject &subject_; // đại diện cho subject mà observer đăng ký
  static int static_number_; // lưu số lượng observer trong hệ thống
  int number_; // số thứ tự Observer trong hệ thống.

 public:
  Observer(Subject &subject) : subject_(subject) {
    this->subject_.Attach(this); // đăng ký observer với subject nhất định
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n"; // cập nhật số lượng observer
    this->number_ = Observer::static_number_; // cập nhật thứ tự của observer vừa tạo.
  }

  virtual ~Observer() {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void Update(const std::string &message_from_subject) override {
    message_from_subject_ = message_from_subject; // cập nhật tin nhắn nhận từ subject.
    PrintInfo();
  }

    // observer tự bỏ subscribe với subject mà nó đăng ký
  void RemoveMeFromTheList() {
    subject_.Detach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }

    // in thông tin của observer
  void PrintInfo() {
    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
  }
};

// khởi tạo số lượng observer
int Observer::static_number_ = 0;


void ClientCode() {
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->CreateMessage("Hello World! :D");
  observer3->RemoveMeFromTheList();

  subject->CreateMessage("The weather is hot today! :p");
  observer4 = new Observer(*subject);

  observer2->RemoveMeFromTheList();
  observer5 = new Observer(*subject);

  subject->CreateMessage("My new car is great! ;)");
  observer5->RemoveMeFromTheList();

  observer4->RemoveMeFromTheList();
  observer1->RemoveMeFromTheList();

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;
}

int main() {
  ClientCode();
  return 0;
}