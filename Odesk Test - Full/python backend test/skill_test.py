__author__ = 'Elias'

class AccountHolder:
    def __init__(self, first_name, last_name, ssn, birthday):
        self.first_name = first_name
        self.last_name = last_name
        self.ssn = ssn
        self.birthday = birthday
    def __str__(self):
       return "Name: " + self.first_name + " " + self.last_name + " SSN: " + self.ssn + " Born: " + str(self.birthday)

class Account:
    def __init__(self, info, number, money, rate):
        self.info = info
        self.number = number
        self.rate = rate
        self.money = money

    def __str__(self):
       return str(self.info) + " your account number "+ self.number + " has $" + "{0:.2f}".format(self.money) + " remaining"

class Checking(Account):

    def withdraw(self, withdraw):
        if self.money >= withdraw:
            self.money -= withdraw

    def deposit(self, deposit):
        if deposit >= 0:
            self.money += deposit

class Saving(Account):

    def deposit(self, deposit):
        if deposit >= 0:
            self.money += deposit

    def withdraw(self, withdraw):
        if self.money >= withdraw:
            self.money -= withdraw


    def add_interest(self):
        self.rate_money = self.money * self.rate / 100 /12
        self.money += self.rate_money

p = AccountHolder('Bob', 'Marley', '123-44-5678', 1966)
bobsChecking = Checking(p, '17890', 412.76, 50)
bobsSaving = Saving(p, '17891', 3087.44, 2.3)
bobsChecking.withdraw(100)
bobsChecking.deposit(49.30)
bobsSaving.deposit(500)
print bobsSaving
bobsSaving.add_interest()
bobsChecking.withdraw(10000)
bobsSaving.withdraw(10000)

print p
print bobsSaving
print bobsChecking