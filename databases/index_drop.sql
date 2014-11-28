use bookfetch;

# Indices for user { first name, last name }
drop index first_name on user;
drop index last_name on user;

# Indices for student { graduation year, birth date, university id }
drop index grad_year on student;
drop index birthdate on student;

# Indices for department { name, university id }
drop index name on department;

# Indices for instructor { first name, last name }
drop index first_name on instructor;
drop index last_name on instructor;

# Indices for course { year, semester }
drop index year on course;
drop index semester on course;

# Indices on employee { salary, role }
drop index salary on employee;
drop index role on employee;

# Indices on tickets { category, status }
drop index category on ticket;
drop index status on ticket;
