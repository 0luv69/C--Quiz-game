# Quiz Game Documentation

## Introduction
The Quiz Game is a simple command-line program written in C. It allows users to play a quiz game, login/signup to their account, and for administrators to manage quiz questions. Users can play the quiz, view their scores, and administrators can add/remove quiz questions. 

## Features
- **User Authentication:** Users can login/signup to their account to play the quiz.
- **Quiz Game:** Users can play the quiz by answering questions and view their scores.
- **Admin Panel:** Administrators can add/remove quiz questions from the game.
- **Help Page:** Provides instructions on how to navigate and use the program.
- **Score Tracking:** Users' scores are tracked and saved in the system.

## Code Structure

### Main Function
Entry point of the program. Displays a welcome message and redirects to the menu page.

### Menu Page
Allows users to choose options like playing the game, logging in, signing up, accessing the admin panel, or exiting the program.

### Help Page
Displays instructions on how to use the program.

### User Authentication
Provides functionalities for user login/signup.

### Admin Panel
Allows administrators to add/remove quiz questions.

### Quiz Game
Implements the quiz game functionality, including displaying questions, accepting user input, and calculating scores.

### Score Tracking
Manages user scores and updates them accordingly.

## Data Structures

- **QuizQuestion Struct:** Represents a quiz question with the question, options, and correct answer.
- **User_struct Struct:** Stores user information including username, total score, and pass code.

## Functions

- `login()`: Handles user login functionality.
- `signup()`: Allows users to sign up for a new account.
- `admin_Page()`: Provides functionalities for administrators to manage quiz questions.
- `addQuestion()`: Allows administrators to add new questions to the quiz.
- `Play_game()`: Implements the quiz game functionality for users to play.
- `DeleteQuestion()`: Allows administrators to remove all questions from the quiz.
- `help_Page()`: Displays instructions on how to use the program.
- `menu_page()`: Main menu page for users to navigate through different options.
- `clearInputBuffer()`: Clears the input buffer.

## File Handling

- **quiz_data.quiz:** Stores quiz questions.
- **user_data.quiz:** Stores user information including username, score, and pass code.

## Usage

1. Run the program.
2. Choose options from the main menu.
3. Follow the prompts to play the quiz, login/signup, or access the admin panel.

## Conclusion

The Quiz Game provides an interactive and engaging way for users to test their knowledge while also offering administrators the ability to manage quiz questions. It demonstrates basic C programming concepts including user input, file handling, and control structures.
