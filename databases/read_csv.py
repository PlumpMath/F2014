import csv

def create_users():
    # Student users
    with open('student.csv') as csvfile, open('data_insertion.sql', 'w') as sqlfile:
        sqlfile.write("use bookfetch;\n")
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
            data = sqlfile.write("(\""
            + row["Fname"] + "\", \""
            + row["Lname"] + "\", \""
            + row["email"] + "\", \""
            + row["address"] + "\"),\n")

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

def main():
    create_users()
    phone_numbers()
    create_universities()

main()
