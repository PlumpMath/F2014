import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Date;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import java.util.Scanner;

public class JDBCInterface {

    private static HashMap<Integer, String> queries = new HashMap<Integer, String>();
    static {
        queries.put(1, "List the details of students attending 'UMBC'.\n");
        queries.put(2, "List the details of students from all universities that are graduate students.\n");
        queries.put(3, "List the details of all students majoring in 'Computer Science' and buying on average more than 2 books.\n");
        queries.put(4, "List the books that have sold the most or have been rented the most.\n");
        queries.put(5, "List by category and subcategories all the books.\n");
        queries.put(6, "List all the book names that are required for a course except books that are of the 'Computer Science' category.\n");
        queries.put(7, "List all books that have been bought by students not associated with a course at a university but have at least two keywords in common with books " +
                       "that are associated with a university.\n" );
        queries.put(8, "List all the books and a count of the number of courses each book has been associated with.\n");
        queries.put(9, "List book titles that are related to 'Linear Algebra'.\n");
        queries.put(10, "List books with ratings higher than 3.\n");
        queries.put(11, "Show a list of books, the number of purchases made, and the overall rating for each book, order by rating.\n");
        queries.put(12, "List the average number of books bought by each student, grouped by category.\n");
        queries.put(13, "List the detais of each university, including departments, courses and number of instructors per course.\n");
        queries.put(14, "For each university, find the total number of books bought that were associated with that university, " +
                        "include the sum and do not forget that books can be bought by students not attending that university.\n");
        queries.put(15, "List each customer service employee and the total number of tickets created.\n");
        queries.put(16, "List the names of administrators, ordered by salary.\n");
        queries.put(17, "List the names of administrators and the average number of tickets closed.\n");
        queries.put(18, "List the tickets grouped by their state, the total number created by a student and the total number created by customer support.\n");
        queries.put(19, "Find the average time it takes for a ticket to go from created to closed.\n");
        queries.put(20, "For each ticket that is closed, show the history of the ticket, order by ticket.\n");
        queries.put(21, "For each student, list the books that are recommended based on our definition of a recommendation.\n");
        queries.put(22, "For each book, list the total sum of students that have purchased books with at least one keyword in common with the book.\n");
        queries.put(23, "List books by ratings and by number of students who rated.");
        queries.put(24, "List books with a rating of 5 and the students who rated the books and their universities.\n");
    };

    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";

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
            String dburl = "jdbc:mysql://localhost/" + database + "?user=" + username + "&password=" + password;
            System.out.println("Establishing connection to " + dburl + "...");
            connection = DriverManager.getConnection(dburl, username, password);
        } catch (SQLException e) {
            System.err.println("Could not connect to database " + database + ". Exiting...");
            e.printStackTrace();
            System.exit(-1);
        }

        return connection;
    }

    public static void clearConsole() {
        System.out.print("\033[H\033[2J");
    }

    public static void mainPrompt(Connection conn) {
        //clearConsole();
        System.out.println("Bookfetch Inc. Database Access");
        System.out.println(
        "Select a module:\n" +
        "1) Students\n" +
        "2) Customer Service\n" +
        "3) Administrator\n" +
        "4) Queries\n" +
        "5) Quit"
        );

        Scanner in = new Scanner(System.in);
        System.out.print("> ");
        String input = in.next();

        switch (input) {
            case "1":
                // Student module
                clearConsole();
                studentModule(conn);
                break;
            case "2":
                // Customer service module
                clearConsole();
                customerServiceModule(conn);
                break;
            case "3":
                // Administrator module
                clearConsole();
                administratorModule(conn);
                break;
            case "4":
                // Queries
                clearConsole();
                queryModule(conn);
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

    private static void addNewStudent(Connection conn) {
        // Get student info.
        Scanner input = new Scanner(System.in);

        System.out.print("\nFirst name: ");
        String first_name = input.nextLine();

        System.out.print("\nLast name: ");
        String last_name = input.nextLine();

        System.out.print("\nAddress: ");
        String address = input.nextLine();

        System.out.print("\nEmail: ");
        String email = input.nextLine();

        System.out.print("\nYear (1-4): ");
        Integer year = Integer.parseInt(input.nextLine());

        System.out.print("\nUnderGrad or Grad? ");
        String student_type = input.nextLine();

        System.out.print("\nBirthdate (MM/DD/YYYY): ");
        String b_str = input.nextLine();

        String[] birthdate_str = b_str.split("/");
        String birthdate = birthdate_str[0] + "-" + birthdate_str[1] + "-" + birthdate_str[2];

        System.out.print("\nUniversity: ");
        String university = input.nextLine();

        // Print summary to the user.
        System.out.println("\nFirst name: " + first_name);
        System.out.println("Last name: " + last_name);
        System.out.println("Address: " + address);
        System.out.println("Email: " + email);
        System.out.println("Year: " + year.toString());
        System.out.println("Student Type: " + student_type);
        System.out.println("Birthdate: " + b_str);

        System.out.print("\nIs this correct (y / n)? ");
        String confirm = input.next();
        if (confirm.toLowerCase().contains("y")) {
            try {
                Statement stmt = conn.createStatement();
                String sql = "insert into user (first_name, last_name, address, email) value (\"" + first_name + "\", \"" + last_name + "\", \"" + address + "\", \"" + email + "\")";
                stmt.executeUpdate(sql);
                System.out.println("Adding new student to database.");
            } catch (Exception e) {
                //System.err.println("An error occurred.");
                //e.printStackTrace();
            }

            try {
                Statement stmt = conn.createStatement();
                // Get user_id.
                String id_query = "select id from user where first_name = \"" + first_name + "\" and last_name = \"" + last_name + "\";";
                ResultSet rs = stmt.executeQuery(id_query);

                int user_id = 0;
                while (rs.next()) user_id = rs.getInt("id");

                id_query = "select id from university where name = \"" + university + "\";";

                rs = stmt.executeQuery(id_query);

                int university_id = 0;
                while(rs.next()) university_id = rs.getInt("id");

                String sql = "insert into student (user_id, year, student_type, birthdate, university_id) values (" + user_id + ", " +
                year + ", \"" + student_type + "\", " + birthdate + ", " + university_id + ");";

                System.out.println(sql);

                stmt.executeUpdate(sql);
            } catch (Exception e) {
                //System.err.println("An error occurred.");
                //e.printStackTrace();
            }
        } else {
            // Back out.
            System.out.println("Aborting the statement...");
        }

        studentModule(conn);
    }

    public static void studentModule(Connection conn) {
        System.out.println(
        "Student Module:\n" +
        "1) Create a new student\n" +
        "2) Create a new cart for a user\n" +
        "3) Create a new order from a cart\n" +
        "4) Create a new book review\n" +
        "5) BACK to main menu");

        Scanner in = new Scanner(System.in);

        while(true) {
            System.out.print("> ");

            String input = in.next();

            switch (input) {
                case "1":
                    addNewStudent(conn);
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
                    mainPrompt(conn);
                    break;
                default:
                    break;
            }
        }
    }

    public static void customerServiceModule(Connection conn) {
        System.out.println(
        "Customer Service Module:\n" +
        "1) New Trouble Ticket\n" +
        "2) Cancel an order\n" +
        "3) BACK to main menu");

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
                    mainPrompt(conn);
                    break;
                default:
                    break;
            }
        }
    }

    public static void administratorModule(Connection conn) {
        System.out.println(
        "Administrators:\n" +
        "1) Add a new book to the inventory\n" +
        "2) Add a new university with department, courses and book associations\n" +
        "\nSuper Administrator:\n" +
        "3) Add a new customer service employee\n" +
        "\nOther:\n" +
        "4) BACK to main menu");

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
                    mainPrompt(conn);
                    break;
                default:
                    break;
            }
        }
    }

    public static void queryModule(Connection conn) {
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
                    for (Map.Entry<Integer, String> entry: queries.entrySet()) {
                        System.out.println(entry.getKey() + ": " + entry.getValue());
                    }
                    System.out.println("Enter a query 1 - 24, or HELP or BACK.");
                    break;
                case "B":
                case "b":
                case "back":
                case "BACK":
                    mainPrompt(conn);
                    break;
                default:
                    System.err.println("Invalid option. Please try again.");
                    break;
            }
        }
    }

    public static void main(String[] args) {

        // Establish connection to DB.
        // Get args.
        if (args != null && args.length == 3) {
            JDBCInterface db = new JDBCInterface();
            Connection conn = null;
            try {
                conn = db.getConnection(args[0], args[1], args[2]);
            } catch (Exception e) {
                e.printStackTrace();
                System.exit(-1);
            }

            mainPrompt(conn);
        } else {
            System.err.println("Wrong number of arguments. Don't forget username password database, in that order.");
        }


    }
}
