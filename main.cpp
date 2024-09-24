#include <iostream>
#include <vector>
#include <ranges>
#include <format>
#include <string>

// Helper function to convert a vector of strings to a formatted string
std::string format_vector(const std::vector<std::string> &vec) {
    std::string result = "{";
    bool first = true;
    for (const auto &s: vec) {
        if (!first) {
            result += ", ";
        }
        result += '"' + s + '"';
        first = false;
    }
    result += "}";
    return result;
}

// 1. Define a concept to constrain to integral types
template<typename T>
concept Integral = std::is_integral_v<T>;

// 2. Function to filter even numbers using concepts and ranges
auto get_even_numbers(const std::vector<int> &numbers) -> std::vector<int> {
    // Use ranges to filter even numbers
    auto even_view = numbers
                     | std::views::filter([](int n) { return n % 2 == 0; });

    // Convert the view to a vector
    return std::vector<int>(even_view.begin(), even_view.end());
}

// 3. Function to square numbers using ranges
auto square_numbers(const std::vector<int> &numbers) -> std::vector<int> {
    // Use ranges to transform (square) each number
    auto squared_view = numbers
                        | std::views::transform([](int n) { return n * n; });

    // Convert the view to a vector
    return std::vector<int>(squared_view.begin(), squared_view.end());
}

// 4. Template function constrained by the Integral concept
template<Integral T>
T sum(const std::vector<T> &numbers) {
    T total = 0;
    for (const auto &num: numbers) {
        total += num;
    }
    return total;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    // Get even numbers
    auto evens = get_even_numbers(numbers);

    // Square the even numbers
    auto squared_evens = square_numbers(evens);

    // Calculate the sum using a constrained template function
    int total = sum(squared_evens);

    // Transform numbers to strings using ranges and collect them into vectors
    auto original_str_view = numbers | std::views::transform([](int n) { return std::to_string(n); });
    std::vector<std::string> original_str(original_str_view.begin(), original_str_view.end());

    auto evens_str_view = evens | std::views::transform([](int n) { return std::to_string(n); });
    std::vector<std::string> evens_str(evens_str_view.begin(), evens_str_view.end());

    auto squared_evens_str_view = squared_evens | std::views::transform([](int n) { return std::to_string(n); });
    std::vector<std::string> squared_evens_str(squared_evens_str_view.begin(), squared_evens_str_view.end());

    // Format and print the results using std::format with the helper function
    std::cout << std::format("Original numbers: {}\n", format_vector(original_str));
    std::cout << std::format("Even numbers: {}\n", format_vector(evens_str));
    std::cout << std::format("Squared even numbers: {}\n", format_vector(squared_evens_str));
    std::cout << std::format("Sum of squared even numbers: {}\n", total);

    return 0;
}
