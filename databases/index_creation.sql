use bookfetch;

# Indices for user { first name, last name }
create index first_name on user (first_name);
create index last_name on user (last_name);

# Indices for student { graduation year, birth date, university id }
create index grad_year on student (grad_year);
create index birthdate on student (birthdate);

# Indices for department { name, university id }
create index name on department (name);

# Indices for instructor { first name, last name }
create index first_name on instructor (first_name);
create index last_name on instructor (last_name);

# Indices for course { year, semester }
create index year on course (year);
create index semester on course (semester);

# Indices on employee { salary, role }
create index salary on employee (salary);
create index role on employee (role);

# Indices on tickets { category, status }
create index category on ticket (category);
create index status on ticket (status);
