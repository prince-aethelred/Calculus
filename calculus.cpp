#include <iostream>
#include <vector>
#include <string>

// Term of a Polynomial Expression
class Term
{
public:
    int coeff, exp;

    Term() : coeff(1), exp(1) {}
    Term(int in_coeff, int in_exp) : coeff(in_coeff), exp(in_exp) {}
    Term(std::string in_string)
    {
        std::string coeff_string = "";
        std::string exp_string = "";
        bool is_coeff = true;
        for (int i = 0; i < in_string.length(); i++)
        {
            if (in_string[i] == 'x')
            {
                is_coeff = false;
            }
            else if (in_string[i] == '^')
            {
                is_coeff = false;
            }
            else if (is_coeff)
            {
                coeff_string += in_string[i];
            }
            else
            {
                exp_string += in_string[i];
            }
        }
        this->coeff = std::stoi(coeff_string);
        this->exp = std::stoi(exp_string);
    }
    ~Term() {}

    // Returns a new Term that is the Derivative of this Term
    Term derive_term()
    {
        Term derived_term;
        derived_term.coeff = this->coeff * this->exp;
        derived_term.exp = this->exp - 1;
        return derived_term;
    }

    // Returns a new Term that is the Integral of this Term
    Term integrate_term()
    {
        Term integrated_term;
        integrated_term.coeff = this->coeff / (this->exp + 1);
        integrated_term.exp = this->exp + 1;
        return integrated_term;
    }

    int getCoeff()
    {
        return this->coeff;
    }
    int getExp()
    {
        return this->exp;
    }
    void setCoeff(int coeff)
    {
        this->coeff = coeff;
    }
    void setExp(int exp)
    {
        this->exp = exp;
    }
    // overload equality operator
    bool operator==(const Term &rhs)
    {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    // overload inequality operator
    bool operator!=(const Term &rhs)
    {
        return this->coeff != rhs.coeff || this->exp != rhs.exp;
    }
    // overload less than operator
    bool operator<(const Term &rhs)
    {
        return this->exp < rhs.exp;
    }
    // overload greater than operator
    bool operator>(const Term &rhs)
    {
        return this->exp > rhs.exp;
    }
    // overload less than or equal to operator
    bool operator<=(const Term &rhs)
    {
        return this->exp <= rhs.exp;
    }
    // overload greater than or equal to operator
    bool operator>=(const Term &rhs)
    {
        return this->exp >= rhs.exp;
    }
    // overload addition operator
    Term operator+(const Term &rhs)
    {
        return Term(this->coeff + rhs.coeff, this->exp);
    }
    // overload subtraction operator
    Term operator-(const Term &rhs)
    {
        return Term(this->coeff - rhs.coeff, this->exp);
    }
};

class Polynomial
{
public:
    std::vector<Term> terms;

    Polynomial() {}
    Polynomial(std::string in_string)
    {
        std::string term_string = "";
        for (int i = 0; i < in_string.length(); i++)
        {
            if (in_string[i] == '+')
            {
                Term term(term_string);
                terms.push_back(term);
                term_string = "";
            }
            else
            {
                term_string += in_string[i];
            }
        }
        Term term(term_string);
        terms.push_back(term);
    }
    ~Polynomial() {}

    Polynomial derive_poly()
    {
        Polynomial derived_poly;
        for (int i = 0; i < terms.size(); i++)
        {
            derived_poly.terms.push_back(terms[i].derive_term());
        }
        return derived_poly;
    }

    Polynomial integrate_poly()
    {
        Polynomial integrated_poly;
        for (int i = 0; i < terms.size(); i++)
        {
            integrated_poly.terms.push_back(terms[i].integrate_term());
        }
        return integrated_poly;
    }

    Polynomial operator+(const Polynomial &rhs)
    {
        Polynomial sum_poly;
        for (int i = 0; i < terms.size(); i++)
        {
            sum_poly.terms.push_back(terms[i]);
        }
        for (int i = 0; i < rhs.terms.size(); i++)
        {
            sum_poly.terms.push_back(rhs.terms[i]);
        }
        return sum_poly;
    }
};

// put each line of string into a vector of strings
std::vector<std::string> split_string(std::string str, char delimiter)
{
    std::vector<std::string> str_vec;
    std::string temp_str = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == delimiter)
        {
            str_vec.push_back(temp_str);
            temp_str = "";
        }
        else
        {
            temp_str += str[i];
        }
    }
    str_vec.push_back(temp_str);
    return str_vec;
}

// split string with newline delimiter
std::vector<std::string> split_string_newline(std::string str)
{
    return split_string(str, '\n');
}

int num_lines(std::string in_string)
{
    int num_lines = 0;
    for (int i = 0; i < in_string.length(); i++)
    {
        if (in_string[i] == '\n')
        {
            num_lines++;
        }
    }
    return num_lines;
}

// find longest line length in a string
auto longest_line_length_of(std::string input_string) -> int
{

    int longest_line_length = 0;
    /**    if (num_lines(input_string) == 1)
        {
            return input_string.length();
        }
        else
        {
    */
    using str_vec = std::vector<std::string>;
    str_vec lines = split_string_newline(input_string);
    longest_line_length = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() > longest_line_length)
        {
            longest_line_length = lines[i].length();
        }
    }
    return longest_line_length;
    //}

    /**
        int current_line_length = input_string.substr(0, input_string.find('\n')).length();
        int longest_line_length = 0;
        for (int i = 0; i < input_string.length(); i++)
        {
            if (input_string[i] == '\n')
            {
                current_line_length = input_string.substr(i + 1, input_string.find('\n')).length();
                if (current_line_length > longest_line_length)
                {
                    longest_line_length = current_line_length;
                }
                current_line_length = 0;
            }
        }
    */
    return longest_line_length;
}

auto print_enclosed_line_in_paragraph(std::string paragraph_string, std::string line_string) -> void
{
    std::cout << "┃" << line_string;
    for (int i = line_string.length(); i < longest_line_length_of(paragraph_string); i++)
    {
        std::cout << " ";
    }
    std::cout << "┃" << std::endl;
}

// print box around a string
// void print_box_around_paragraph(std::string str)
auto print_box_around_paragraph(std::string str) -> void
{
    int str_length = str.length();
    int longest_line_length = longest_line_length_of(str);
    int num_of_lines = num_lines(str);
    std::cout << "┏";
    for (int i = 0; i < longest_line_length; i++)
    {
        std::cout << "━";
    }
    std::cout << "┓" << std::endl;
    // std::cout << "┃" << str << "┃" << std::endl;
    std::vector<std::string> str_lines = split_string_newline(str);

    for (int i = 0; i < num_of_lines; i++)
    {
        print_enclosed_line_in_paragraph(str, str_lines[i]);
    }
    std::cout << "┗";
    for (int i = 0; i < longest_line_length; i++)
    {
        std::cout << "━";
    }
    std::cout << "┛" << std::endl;
}

int main(int argc, char *argv[])
{
    std::string title = "Polynomial Calculator\n";
    // print box around program description
    print_box_around_paragraph(title);
    print_box_around_paragraph("Calculus\n");

    std::string menu =
        "This program will take a polynomial and perform the following operations:\n"
        "1. Derive\n"
        "2. Integrate\n"
        "3. Add\n"
        "4. Subtract\n"
        "5. Multiply\n"
        "6. Divide\n"
        "7. Quit\n"
        "Enter the number of the operation you would like to perform:\n";
    int line_length = menu.substr(0, menu.find("\n")).length();
    int length = 0;
    int longest_length = 0;
    // find the longest line in the menu
    for (int i = 0; i < menu.length(); i++)
    {
        if (menu[i] == '\n')
        {
            if (length > longest_length)
            {
                longest_length = length;
            }
            length = 0;
        }
        else
        {
            length++;
        }
    }

    int menu_box_length = longest_line_length_of(menu);

    // find number of lines in menu
    int num_menu_lines = num_lines(menu);

    // print menu box
    print_box_around_paragraph(menu);

    Term t1("3x^2");
    Term t2("4x^3");
    Term t3("5x^2");
    Term t4("6x^1");
    Term t5("7x^0");
    std::vector<Term> terms = {t1, t2, t3, t4, t5};
    std::vector<Term>::iterator it;
    for (int i = 0; i < terms.size(); i++)
    {
        std::cout << "Original Term: " << terms[i].getCoeff() << "x^" << terms[i].getExp() << " ";
        Term der_term = terms[i].derive_term();
        std::cout << "Derivative: " << der_term.getCoeff() << "x^" << der_term.getExp() << " ";
        Term int_term = terms[i].integrate_term();
        std::cout << "Integral: " << int_term.getCoeff() << "x^" << int_term.getExp() << std::endl;
        // std::cout << terms[i].derive_term().getCoeff() << "x^" << terms[i].derive_term().getExp() << std::endl;
    }

    return 0;
}