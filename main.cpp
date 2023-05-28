#include <iostream>
#include <random>

void print_intro()
{
    std::cout << "Welcome to the Casino!\n";
    std::cout << "Since you are new here, have this as a welcoming gift!\n";

    std::cout << "Balance: $500\n";

    std::cout << "\nThere two game modes (sign and number) choose sign to guess whether the random number\n"
                 "from the range [-10, 10] is positive (x2 win), negative (x2 win) or equal to 0 (x10 win).\n"
                 "Choose number to guess the exact number from the range [1, 7] (x5 win). You can stop playing whenever you want!\n\n";
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
            std::cout << "Sorry, this game is not available here.\n";
        }
    }

    return game;
}

int get_bet(int balance)
{
    int bet;

    while (true)
    {
        std::cout << "Your bet: ";
        std::cin >> bet;

        if (bet >= 0 && bet <= balance)
        {
            break;
        }
        else
        {
            std::cout << "Stop joking around, this is a serious place.\n";
        }
    }

    return bet;
}

int num_game(int bet)
{
    int guess;

    std::cout << "Choose your number: ";
    std::cin >> guess;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 7);

    int number = dist(rng);
    std::cout << "The number: " << number << std::endl;

    if (guess == number)
    {
        std::cout << "Congratulations! You won $" << bet * 5 << "!\n";
        return bet * 5;
    }
    else {
        std::cout << "Sorry, you lost your $" << bet << ".\n";
        return -bet;
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

        if (game == "num")
        {
            balance += num_game(bet);
            std::cout << "Balance: $" << balance << "\n\n";
        }
    }

    std::cout << "Well, there goes your welcoming gift, next time come with your own money to test the luck again!\n";

    return 0;
}
