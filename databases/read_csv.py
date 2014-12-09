import csv


def create_users():
    # Student users
    with open('student.csv') as csvfile, open('data_insertion.sql', 'w') as sqlfile:
        sqlfile.write("use bookfetch;\n\n")
        sqlfile.write("insert into user (first_name, last_name, email, address) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(\""
                          + row["First_name"] + "\", \""
                          + row["Last_name"] + "\", \""
                          + row["email"] + "\", \""
                          + row["Address"] + "\"),\n")

    # Employees
    with open('employees.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(\""
                          + row["Fname"] + "\", \""
                          + row["Lname"] + "\", \""
                          + row["email"] + "\", \""
                          + row["address"] + "\"),\n")

        sqlfile.write("\n")


def phone_numbers():
    # Students
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into phone_number (user_id, phone_number) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("("
                          + "(select id from user where first_name = \""
                          + row["First_name"] + "\" and last_name=\""
                          + row["Last_name"] + "\"), " + row["Telephone"] + "),\n")

    with open('employees.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("("
                          + "(select id from user where first_name = \""
                          + row["Fname"] + "\" and last_name=\""
                          + row["Lname"] + "\"), " + "".join(row["telephone"].split("-")) + "),\n")

        sqlfile.write("\n")


def create_universities():
    with open('employees.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into univerity (name, repr_first_name, repr_last_name, repr_email) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            if row['Role'] == "College Rep":
                sqlfile.write("(\""
                              + row['Company'] + "\", \""
                              + row['Fname'] + "\", \""
                              + row['Lname'] + "\", \""
                              + row['email'] + "\"),\n")

        sqlfile.write("\n")


def create_students():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into student (user_id, year, student_type, birthdate, university_id) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write(
                "(select id from user where first_name = \"" +
                row['First_name'] + "\" and last_name = \"" +
                row['Last_name'] + "\"), " + row['year'] + ", \"" +
                row['student_status'] + "\", " +
                '-'.join(row['birth_date'].split("/")) +
                ", (select id from university where name = \"" +
                row['University'] + "\")),\n")

        sqlfile.write("\n")


def create_carts():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into cart (student_id, date_created, date_updated) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("((select id from user where first_name = \"" +
                          row['First_name'] + "\" and last_name = \"" +
                          row['Last_name'] + "\"), " + row['Cart_created'] +
                          ", " + row['Cart_updated'] + "),\n")

        sqlfile.write("\n")


def create_orders():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into book_order (student_id, date_created, date_fulfilled, " +
                      "shipping_type, cc_number, cc_expiration, cc_name, cc_type, order_status) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "(select id from user where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\"), " +
                          '-'.join(row['ORDER_date_created'].split("/")) + ", " +
                          '-'.join(row['ORDER_date_completed'].split("/")) + ", " +
                          "\"" + row['ORDER_ship_type'] + "\", " +
                          row['ORDER_credit_card'].lower() + ", " +
                          '-'.join(row['ORDER_creditcard_expiry'].split("/")) + ", " +
                          "\"" + row['ORDER_creditcard_name'] + "\", " +
                          "\"" + row['ORDER_creditcard_type'] + "\", " +
                          "\"" + row['ORDER_status'] + "\"" +
                          "),\n")

        sqlfile.write("\n")


def create_departments():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into department (name, university_id) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "\"" + row['major'] + "\", " +
                          "(select id from university where name = \"" + row['University'] + "\")"
                          "),\n")

        sqlfile.write("\n")

    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into department (name, university_id) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "\"" + row['Department'] + "\", " +
                          "(select id from university where name = \"" + row['University'] + "\")"
                          "),\n")

        sqlfile.write("\n")


def create_instructors():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write('insert into instructor (first_name, last_name, dept_id, university_id) values\n')

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "\"" + row['instructor_fname'] + "\", " +
                          "\"" + row['instructor_lname'] + "\", " +
                          "(select id from department where name = \"" + row['Department'] + "\"), " +
                          "(select id from university where name = \"" + row['University'] + "\")"
                          "),\n")

        sqlfile.write("\n")


def create_book_ids():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into book_id (title, isbn, isbn_13) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "\"" + row['book'] + "\", " +
                          row['ISBN'] + ", " +
                          "".join(row['ISBN-13'].split("-")) + "),\n")

        sqlfile.write("\n")


def create_books():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into book (id, type, book_format, price, quantity, published_date, edition, language, weight, rating) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "(select id from book_id where title = \"" +
                          row['book'] + "\"), \"" + row['type'] + "\", \"" +
                          row['format'] + "\", " + row['price'] + ", " +
                          row['quantity'] + ", " + row['publishdate'] + ", " +
                          row['edition_number'] + ", " + row['lang'] + ", " +
                          row['weight_pound'] + ", " + row['ratings'] +
                          "),\n")

        sqlfile.write("\n")


def create_purchases():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into purchases (book_id, student_id, purchase_type) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" + "(select id from book_id where title = \"" + row['CART_book1'] + "\"), " +
                          "(select id from student where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\"), \"" +
                          row['CART_book1_purchased_or_rented'] + "\", " + row['CART_book1_quantity'] + "),\n")

            sqlfile.write("(" + "(select id from book_id where title = \"" + row['Cart_book2'] + "\"), " +
                          "(select id from student where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\"), \"" +
                          row['CART_book2_purchased_or_rented'] + "\", " + row['CART_book2_quantity'] + "),\n")

        sqlfile.write("\n")

    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into purchases (book_id, student_id, purchase_type) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" + "(select id from book_id where title = \"" + row['ORDER_book1'] + "\"), " +
                          "(select id from student where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\"), \"" +
                          row['ORDER_book1_purchased_or_rented'] + "\", " + row['ORDER_book1_quantity'] + "),\n")

            sqlfile.write("(" + "(select id from book_id where title = \"" + row['ORDER_book2'] + "\"), " +
                          "(select id from student where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\"), \"" +
                          row['ORDER_book2_purchased_or_rented'] + "\", " + row['ORDER_book2_quantity'] + "),\n")

        sqlfile.write("\n")


def create_course():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into course (name, year, semester, university_id, instructor_id, book_id) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            sqlfile.write("(" +
                          "\"" + row['Courses'] + "\", " + row['year'] + ", " +
                          row['semester'] + ", (select id from university where name = \"" +
                          row['University'] + "\"), (select id from instructor where first_name = \"" +
                          row['instructor_fname'] + "\" and last_name = \"" + row['instructor_lname'] + "\"), " +
                          "(select book_id from book_id where title = \"" + row['book'] + "\")),\n")

        sqlfile.write("\n")


def create_category():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into category (book_id, category_name) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            # Split categories into list.
            category = row['category'].split(",")[0]
            book_id = "(select book_id from book_id where title = \"" + row['book'] + "\")"
            sqlfile.write("(" + book_id + ", \"" + category + "\"),\n")

        sqlfile.write("\n")


def create_subcategory():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into subcategory (book_id, subcategory_name) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            # Split categories into list.
            categories = row['category'].split(",")[1:]
            book_id = "(select book_id from book_id where title = \"" + row['book'] + "\")"
            for subcategory in categories:
                sqlfile.write("(" + book_id + ", \"" + subcategory + "\"),\n")

        sqlfile.write("\n")


def create_keyword():
    with open('teacher.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into keyword (book_id, keyword) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            # Split keywords into set.
            keywords = set(row['keywords'].split(" "))
            book_id = "(select book_id from book_id where title = \"" + row['book'] + "\")"
            for keyword in keywords:
                sqlfile.write("(" + book_id + ", \"" + keyword + "\"),\n")

        sqlfile.write("\n")


def create_employees():
    with open('employees.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into employee (user_id, salary, role, ssn) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            user_id = "(select id from user where first_name = \"" + row['Fname'] + "\" and last_name = \"" + row['Lname'] + "\")"
            sqlfile.write("(" + user_id + ", " + row['Salary'] + ", " +
                          "\"" + row['Role'] + "\", " + "".join(row['SSN'].split("-")) + "),\n")

        sqlfile.write("\n")


def create_tickets():
    with open('student.csv') as csvfile, open('data_insertion.sql', 'a') as sqlfile:
        sqlfile.write("insert into ticket (category, title, date_logged, problem, solution, status, creator_id, csrep_id, admin_id) values\n")

        reader = csv.DictReader(csvfile)
        for row in reader:
            category = row['Trouble_Category']
            title = row['Trouble_title']
            date_logged = "-".join(row['Trouble_datelogged'].split("/"))
            problem = row['Trouble_description']
            solution = row['Trouble_solution']
            status = row['Trouble_status']
            creator_id = "(select id from user where first_name = \"" + row['First_name'] + "\" and last_name = \"" + row['Last_name'] + "\")"
            csrep_id = "(select id from employee where user_id = (select id from user where first_name = \"" + row['Trouble_customerserviceemployee'] + "\") and role = \"Customer Support\")"
            admin_id = "(select id from employee where user_id = (select id from user where first_name = \"" + row['Trouble_administrator'] + "\") and role = \"Administrators\")"
            sqlfile.write("(" + "\"" + category + "\", \"" + title + "\", " + date_logged +
                          ", \"" + problem + "\", \"" + solution + "\", \"" + status + "\", " + creator_id + ", " +
                          csrep_id + ", " + admin_id + "),\n")

        sqlfile.write("\n")


def create_modifications():
    pass


def create_recommendations():
    pass


def main():
    # create_users()
    # phone_numbers()
    # create_universities()
    # create_students()
    # create_carts()
    # create_orders()
    # create_departments()
    # create_instructors()
    # create_book_ids()
    # create_books()
    create_purchases()
    # create_course()
    # create_category()
    # create_subcategory()
    # create_keyword()
    # create_employees()
    # create_tickets()
    # create_modifications()
    # create_recommendations()

main()
