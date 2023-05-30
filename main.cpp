#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

std::string won_text = "Congratulations! You won $";
std::string lost_text = "Sorry, you lost your $";
std::string bad_input_text = "Stop joking around, this is a serious place.\n";

bool check_if_number(const std::string& s)
{
    for (char c: s)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }

    return true;
}

void print_intro()
{
    std::cout << "Welcome to the Casino!\n";
    std::cout << "Since you are new here, have this as a welcoming gift!\n";

    std::cout << "Balance: $500\n";

    std::cout << "\nThere two game modes (sign and number) choose sign to guess whether the random number\n"
                 "from the range [-10, 10] is positive (x2 win), negative (x2 win) or equal to 0 (x10 win).\n"
                 "Choose number to guess the exact number from the range [1, 7] (x5 win). \n"
                 "Try to hold on to your money for as long as possible!\n\n";
}

std::string get_game()
{
    std::string game;

    while (true)
    {
        std::cout << "Choose you game (sign/num): ";
        std::cin >> game;

        if (game == "sign" || game == "num")
        {
            break;
        }
        else
        {
            std::cout << bad_input_text;
        }
    }

    return game;
}

int get_bet(int balance)
{
    std::string str_bet;
    int bet = -1;

    while (true)
    {
        std::cout << "Your bet: ";
        std::cin >> str_bet;

        if (check_if_number(str_bet))
        {
            bet = std::stoi(str_bet);
        }

        if (bet >= 0 && bet <= balance)
        {
            break;
        }

        std::cout << bad_input_text;
    }

    return bet;
}

int get_random_number(int a, int b)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);

    int number = dist(rng);
    std::cout << "The number: " << number << std::endl;

    return number;
}

int num_game(int bet)
{
    std::string str_guess;
    int guess = -1;

    while (true)
    {
        std::cout << "Choose your number: ";
        std::cin >> str_guess;

        if (check_if_number(str_guess))
        {
            guess = std::stoi(str_guess);
        }

        if (guess >= 1 && guess <= 7)
        {
            break;
        }

        std::cout << bad_input_text;
    }

    int number = get_random_number(1, 7);

    if (guess == number)
    {
        std::cout << won_text << bet * 5 << "!\n";
        return bet * 5;
    }
    else {
        std::cout << lost_text << bet << ".\n";
        return 0;
    }
}

int sign_game(int bet)
{
    char guess = ' ';
    std::vector<char> options = {'-', '0', '+'};

    while (std::find(options.begin(), options.end(), guess) == options.end())
    {
        std::cout << "Choose your sign (-/0/+): ";
        std::cin >> guess;
    }

    int number = get_random_number(-10, 10);

    if ((guess == '-' && number < 0) || (guess == '+' && number > 0))
    {
        std::cout << won_text << bet * 2 << "!\n";
        return bet * 2;
    }
    else if (guess == '0' && number == 0)
    {
        std::cout << won_text << bet * 10 << "!\n";
        return bet * 10;
    }
    else
    {
        std::cout << lost_text << bet << ".\n";
        return 0;
    }
}

int main() {
    print_intro();

    int balance = 500;
    int bet;
    std::string game;

    while (balance > 0)
    {
        game = get_game();
        bet = get_bet(balance);
        balance -= bet;

        if (game == "num")
        {
            balance += num_game(bet);
        }
        else
        {
            balance += sign_game(bet);
        }

        std::cout << "Balance: $" << balance << "\n\n";
    }

    std::cout << "Well, there goes your welcoming gift, next time come with your own money to test the luck again!\n";

    return 0;
}
