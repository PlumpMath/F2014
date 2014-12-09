/* List all UMBC students */
select * from user join student where user.id = user_id and university_id = (select id from university where name = "UMBC");

/* List details of all students from all universities that are grad students */
select * from user join student where user.id = user_id and student_type = "Grad";

/* List of all students majoring in Computer Science and buying on average more than two books. */
select * from user join student where student.major = "Computer Science" and (select avg(quantity) from purchase where user_id = user.id) > 2;

/* List all the books that have been sold or rented the most */

/* List by category and subcategory all the books. */
select title

/* List all books required by a course except that are of the 'Computer Science' category.

* /List all books that have been bought by students not associated with a course at a university but have at least two keywords in common with books that are associated with a university. */

/* List all the books and a count of the number of courses each book has been associated with. */

/* List book titles that are related to 'Linear Algebra'. */
select title from book_id where (select subcategory_name from subcategory where subcategory_name like "Linear Algebra") and (select category_name from category where category_name like "Linear Algebra");

/* List books with ratings higher than 3. */
select * from book where rating > 3;

/* Show a list of books, the number of purchases made, and the overall rating for each book, order by rating. */

/* List the average number of books bought by each student, grouped by category. */

/* List the detais of each university, including departments, courses and number of instructors per course. */

/* For each university, find the total number of books bought that were associated with that university,
   include the sum and do not forget that books can be bought by students not attending that university. */

/* List each customer service employee and the total number of tickets created. */
select *, ticket_count as ticket_count = (select count(id) from ticket where creator_id = user_id) from employee where role = "Customer Support";

/* List the names of administrators, ordered by salary. */
select * from employee where role = "Administrators" order by salary;

/* List the names of administrators and the average number of tickets closed. */

/* List the tickets grouped by their state, the total number created by a student and the total number created by customer support. */

/* Find the average time it takes for a ticket to go from created to closed. */

/* For each ticket that is closed, show the history of the ticket, order by ticket. */

/* For each student, list the books that are recommended based on our definition of a recommendation. */

/* For each book, list the total sum of students that have purchased books with at least one keyword in common with the book. */

/* List books by ratings and by number of students who rated. */

/* List books with a rating of 5 and the students who rated the books and their universities. */
