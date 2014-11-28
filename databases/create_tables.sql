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
  phone_number numeric(10),
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
  grad_year year(4),
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
  date_created timestamp not null,
  date_updated timestamp
);

create table book_order (
  student_id int not null,
  foreign key (student_id)
    references student(user_id)
    on delete cascade,
  date_created timestamp not null,
  date_fulfilled timestamp,
  shipping_type varchar(10),
  cc_number numeric(16),
  cc_expiration numeric(4),
  cc_name varchar(200),
  cc_type varchar(20),
  order_status varchar(20)
);

create table department (
  id int auto_increment not null,
  primary key (id),
  name varchar(200),
  university_id int,
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
  isbn numeric(10),
  isbn_13 numeric(13)
);

create table book (
  id int,
  foreign key (id)
    references book_id(id)
    on delete cascade,
  used_or_new varchar(4),
  book_format varchar(20),
  price numeric(6, 2),
  quantity int,
  published_date timestamp,
  edition_number int,
  language varchar(20),
  weight numeric(3, 1),
  rating numeric(2, 1)
);

create table purchase (
  book_id int not null,
  foreign key (book_id)
    references book (id)
    on delete cascade,
  student_id int not null,
  foreign key (student_id)
    references student(user_id)
    on delete cascade,
  purchase_type varchar(5)
);

create table course (
  id int auto_increment not null,
  primary key (id),
  name varchar(200),
  year year(4),
  semester varchar(6),
  section_number int,
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

create table keywords (
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
  assignee_id int,
  foreign key (assignee_id)
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
