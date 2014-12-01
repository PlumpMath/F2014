import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

import java.util.Scanner;

public class JDBCInterface {

    private static String queries = "1. List the details of students attending 'UMBC'.\n" +
                             "2. List the details of students from all universities " +
                             "that are graduate students.\n" +
                             "3. List the details of all students majoring in " +
                             "'Computer Science' and buying on average more than 2 books.\n" +
                             "4. List the books that have sold the most or have been rented the most.\n" +
                             "5. List by category and subcategories all the books.\n" +
                             "6. List all the book names that are required for a course except books " +
                             "that are of the 'Computer Science' category.\n" +
                             "7. List all books that have been bought by students not associated with a " +
                             "course at a university but have at least two keywords in common with books " +
                             "that are associated with a university.\n" +
                             "8. List all the books and a count of the number of courses each book has been " +
                             "associated with.\n" +
                             "9. List book titles that are related to 'Linear Algebra'.\n" +
                             "10. List books with ratings higher than 3.\n" +
                             "11. Show a list of books, the number of purchases made, and the overall rating " +
                             "for each book, order by rating.\n" +
                             "12. List the average number of books bought by each student, grouped by category.\n" +
                             "13. List the detais of each university, including departments, courses and number of " +
                             "instructors per course.\n" +
                             "14: For each university, find the total number of books bought that were associated " +
                             "with that university, include the sum and do not forget that books can be bought by students " +
                             "not attending that university.\n" +
                             "15. List each customer service employee and the total number of tickets created.\n" +
                             "16. List the names of administrators, ordered by salary.\n" +
                             "17. List the names of administrators and the average number of tickets closed.\n" +
                             "18. List the tickets grouped by their state, the total number created by a student " +
                             "and the total number created by customer support.\n" +
                             "19. Find the average time it takes for a ticket to go from created to closed." +
                             "20. For each ticket that is closed, show the history of the ticket, order by ticket.\n" +
                             "21. For each student, list the books that are recommended based on our definition of a " +
                             "recommendation.\n" +
                             "22. For each book, list the total sum of students that have purchased books with at least one " +
                             "keyword in common with the book.\n" +
                             "23. List books by ratings and by number of students who rated." +
                             "24. List books with a rating of 5 and the students who rated the books and their universities.\n";

    static final String JDBC_DRIVER = "com.mysql.jdbc.driver";

    private Connection getConnection(String username, String password, String database) {
        Connection connection = null;
        try {
            System.out.println("Testing driver...");
            Class.forName(JDBC_DRIVER);
        } catch (ClassNotFoundException e) {
            System.err.println("FAILURE:: JDBC Driver cannot be found!");
            e.printStackTrace();
            System.exit(-1);
        }

        try {
            String dburl = "jbdc:mysql://localhost/" + database + "?user=" + username + "&password=" + password;
            System.out.println("Establishing connection...");
            connection = DriverManager.getConnection(dburl, username, password);
        } catch (SQLException e) {

        }

        return connection;
    }

    public static void clearConsole() {
        System.out.print("\033[H\033[2J");
    }

    public static void mainPrompt() {
        clearConsole();
        System.out.println("Bookfetch Inc. Database Access");
        System.out.println(
        "Select a module:\n" +
        "\t1) Students\n" +
        "\t2) Customer Service\n" +
        "\t3) Administrator\n" +
        "\t4) Queries\n" +
        "\t5) Quit"
        );

        Scanner in = new Scanner(System.in);
        System.out.print("> ");
        String input = in.next();

        switch (input) {
            case "1":
                // Student module
                clearConsole();
                studentModule();
                break;
            case "2":
                // Customer service module
                clearConsole();
                customerServiceModule();
                break;
            case "3":
                // Administrator module
                clearConsole();
                administratorModule();
                break;
            case "4":
                // Queries
                clearConsole();
                queryModule();
                break;
            case "5":
            case "q":
            case "Q":
            case "QUIT":
            case "quit":
            case "Quit":
                System.out.println("Goodbye.");
                System.exit(0);
                break;
            default:
                break;
        }
    }

    public static void studentModule() {
        System.out.println(
        "Student Module:\n" +
        "\t1) Create a new student\n" +
        "\t2) Create a new cart for a user\n" +
        "\t3) Create a new order from a cart\n" +
        "\t4) Create a new book review\n" +
        "\t5) BACK to main menu");

        Scanner in = new Scanner(System.in);

        while(true) {
            System.out.print("> ");

            String input = in.next();

            switch (input) {
                case "1":
                    System.out.println("Not implemented yet.");
                    break;
                case "2":
                    System.out.println("Not implemented yet.");
                    break;
                case "3":
                    System.out.println("Not implemented yet.");
                    break;
                case "4":
                    System.out.println("Not implemented yet.");
                    break;
                case "5":
                case "b":
                case "B":
                case "BACK":
                case "back":
                    mainPrompt();
                    break;
                default:
                    break;
            }
        }
    }

    public static void customerServiceModule() {
        System.out.println(
        "Customer Service Module:\n" +
        "\t1) New Trouble Ticket\n" +
        "\t2) Cancel an order\n" +
        "\t3) BACK to main menu");

        Scanner in = new Scanner(System.in);

        while(true) {
            System.out.print("> ");

            String input = in.next();

            switch (input) {
                case "1":
                    System.out.println("Not implemented yet.");
                    break;
                case "2":
                    System.out.println("Not implemented yet.");
                    break;
                case "3":
                case "b":
                case "B":
                case "BACK":
                case "back":
                    mainPrompt();
                    break;
                default:
                    break;
            }
        }
    }

    public static void administratorModule() {
        System.out.println(
        "Administrators:\n" +
        "\t1) Add a new book to the inventory\n" +
        "\t2) Add a new university with department, courses and book associations\n" +
        "\nSuper Administrator:\n" +
        "\t3) Add a new customer service employee\n" +
        "\nOther:\n" +
        "\t4) BACK to main menu");

        Scanner in = new Scanner(System.in);

        while(true) {
            System.out.print("> ");

            String input = in.next();

            switch (input) {
                case "1":
                    System.out.println("Not implemented yet.");
                    break;
                case "2":
                    System.out.println("Not implemented yet.");
                    break;
                case "3":
                    System.out.println("Not implemented yet.");
                    break;
                case "4":
                case "b":
                case "B":
                case "BACK":
                case "back":
                    mainPrompt();
                    break;
                default:
                    break;
            }
        }
    }

    public static void queryModule() {
        System.out.println("Enter a query 1 - 24, or HELP or BACK.");
        Scanner in = new Scanner(System.in);
        while (true) {
            // Display queries
            System.out.print("> ");

            String input = in.next();

            switch (input) {
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                case "10":
                case "11":
                case "12":
                case "13":
                case "14":
                case "15":
                case "16":
                case "17":
                case "18":
                case "19":
                case "20":
                case "21":
                case "22":
                case "23":
                case "24":
                    System.out.println("Case " + input);
                    break;
                case "h":
                case "H":
                case "help":
                case "HELP":
                    System.out.println("Here is a list of the queries by number:");
                    System.out.println(queries);
                    break;
                case "B":
                case "b":
                case "back":
                case "BACK":
                    mainPrompt();
                    break;
                default:
                    System.err.println("Invalid option. Please try again.");
                    break;
            }
        }
    }

    public static void main(String args[]) {

        // Establish connection to DB.
        mainPrompt();
    }
}
