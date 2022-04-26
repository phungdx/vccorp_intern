#include<iostream>

/**
 * Subsystem có thể chấp nhận requests từ facade hoặc trực tiếp từ client.
 * Trong bất cứ trường hợp nào, thì với subsystem, facade cũng được coi như 
 * 1 client khác.
 */
class Subsystem1 {
 public:
  std::string Operation1() const {
    return "Subsystem1: Ready!\n";
  }
  // ...
  std::string OperationN() const {
    return "Subsystem1: Go!\n";
  }
};
/**
 * 1 số facades có thể hoạt động được với nhiều subsytems
 */
class Subsystem2 {
 public:
  std::string Operation1() const {
    return "Subsystem2: Get ready!\n";
  }
  // ...
  std::string OperationZ() const {
    return "Subsystem2: Fire!\n";
  }
};

/**
 * Class Facade cung cấp 1 interface đơn giản với logic phức tạp của 1 hay một vài
 * subsytems. Facade ủy thác requests của client tới các objects phù hợp trong subsytem.
 * Facade cũng chịu trách nhiệm quản lý dòng đời của chúng. Tất cả nhằm tách client khỏi
 * sự phức tạp ko mong muốn của subsystems.
 */
class Facade {
 protected:
  Subsystem1 *subsystem1_;
  Subsystem2 *subsystem2_;
  /**
   */
 public:
  /**
   */
  Facade(
      Subsystem1 *subsystem1 = nullptr,
      Subsystem2 *subsystem2 = nullptr) {
    this->subsystem1_ = subsystem1 ?: new Subsystem1;
    this->subsystem2_ = subsystem2 ?: new Subsystem2;
  }

  ~Facade() {
    delete subsystem1_;
    delete subsystem2_;
  }
  /**
   * Các phương thức của Facade là các shortcuts tiện lợi đến chức năng phức tạp của
   * các subsystems. Tuy nhiên, clients chỉ nhận được 1 phần nhỏ khả năng của subsystem.
   */
  std::string Operation() {
    std::string result = "Facade initializes subsystems:\n";
    result += this->subsystem1_->Operation1();
    result += this->subsystem2_->Operation1();
    result += "Facade orders subsystems to perform the action:\n";
    result += this->subsystem1_->OperationN();
    result += this->subsystem2_->OperationZ();
    return result;
  }
};

/**
 * Code của Client làm việc với các subsystems phức tạp thông qua một interface đơn giản
 * cung cấp bởi facade.
 * Khi 1 facade quản lý vòng đời của 1 subsystem, client có thể ko biết về sự tồn tại của subsystem
 * Cách tiếp cận này giúp ta giữ độ phức tạp trong tầm kiểm soát
 */
void ClientCode(Facade *facade) {
  // ...
  std::cout << facade->Operation();
  // ...
}
/**
 * Code của client có thể có 1 vài objects đã tồn tại của subsystem.
 * Trong trường hợp đó, nên khởi tạo facade với objects này thay vì
 * để facade khởi tạo các instances mới.
 */

int main() {
  Subsystem1 *subsystem1 = new Subsystem1;
  Subsystem2 *subsystem2 = new Subsystem2;
  Facade *facade = new Facade(subsystem1, subsystem2);
  ClientCode(facade);

  delete facade;

  return 0;
}