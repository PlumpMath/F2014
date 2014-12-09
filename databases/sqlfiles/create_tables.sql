drop database if exists bookfetch;
create database bookfetch;

use bookfetch;

create table user (
  id int not null auto_increment,
  primary key (id),
  first_name varchar(50),
  last_name varchar(50),
  address varchar(200),
  email varchar(100)
);

create table phone_number (
  phone_num varchar(10),
  user_id int,
  foreign key (user_id)
    references user(id)
    on delete cascade
);

create table university (
  id int auto_increment not null,
  primary key (id),
  name varchar(200),
  repr_first_name varchar(50),
  repr_last_name varchar(50),
  repr_email varchar(100)
);

create table student (
  user_id int not null,
  foreign key (user_id)
    references user(id)
    on delete cascade,
  year int,
  student_type varchar(10),
  birthdate date,
  university_id int not null,
  foreign key (university_id)
    references university(id)
);

create table cart (
  student_id int not null,
  foreign key (student_id)
    references student(user_id)
    on delete cascade,
  date_created timestamp default current_timestamp,
  date_updated timestamp
);

create table book_order (
  student_id int not null,
  foreign key (student_id)
    references student(user_id)
    on delete cascade,
  date_created date not null,
  date_fulfilled date,
  shipping_type varchar(10),
  cc_number varchar(16),
  cc_expiration date,
  cc_name varchar(200),
  cc_type varchar(20),
  order_status varchar(20)
);

create table department (
  id int auto_increment not null,
  primary key (id),
  name varchar(200),
  university_id int not null,
  foreign key (university_id)
    references university(id)
);

create table instructor (
  id int not null auto_increment,
  primary key (id),
  first_name varchar(50),
  last_name varchar(50),
  dept_id int,
  foreign key (dept_id)
    references department(id),
  university_id int,
  foreign key (university_id)
    references university(id)
);

create table book_id (
  id int not null auto_increment,
  primary key (id),
  title varchar(200),
  isbn numeric(11),
  isbn_13 numeric(14)
);

create table book (
  id int,
  foreign key (id)
    references book_id(id)
    on delete cascade,
  type char(3),
  book_format varchar(20),
  price numeric(6, 2),
  quantity int,
  published_date year(4),
  edition_number int,
  language varchar(20),
  weight numeric,
  rating numeric (2, 1)
);

create table purchase (
  book_id int not null,
  foreign key (book_id)
    references book (id)
    on delete cascade,
  student_id int not null,
  foreign key (student_id)
    references user(id)
    on delete cascade,
  purchase_type varchar(5),
  quantity int
);

create table course (
  id int auto_increment not null,
  primary key (id),
  name varchar(200),
  year int,
  semester varchar(6),
  university_id int,
  foreign key (university_id)
    references university(id)
    on delete cascade,
  instructor_id int,
  foreign key (instructor_id)
    references instructor(id)
    on delete cascade,
  book_id int,
  foreign key (book_id)
    references book(id)
    on delete cascade
);

create table category (
  book_id int,
  foreign key (book_id)
    references book(id),
  category_name varchar(200)
);

create table subcategory (
  book_id int,
  foreign key (book_id)
    references book(id),
  subcategory_name varchar(200)
);

create table keyword (
  book_id int,
  foreign key (book_id)
    references book(id),
  keyword varchar(200)
);

create table employee (
  user_id int not null,
  foreign key (user_id)
    references user(id)
    on delete cascade,
  salary numeric(8, 2),
  role varchar(20),
  ssn numeric(9)
);

create table ticket (
  id int not null auto_increment,
  primary key (id),
  category varchar(50),
  title varchar(50),
  date_logged timestamp not null,
  date_completed timestamp,
  problem varchar(200),
  solution varchar(200),
  status varchar(10),
  creator_id int,
  foreign key (creator_id)
    references user(id),
  csrep_id int,
  foreign key (csrep_id)
    references employee(user_id),
  admin_id int,
  foreign key (admin_id)
    references employee(user_id)
);

create table modifications (
  ticket_id int,
  foreign key (ticket_id)
    references ticket(id),
  date_modified timestamp,
  new_status varchar(10)
);

create table recommendations (
  user_id int not null,
  foreign key (user_id)
    references student (user_id),
  book_id int not null,
  foreign key (book_id)
    references book (id)
);
