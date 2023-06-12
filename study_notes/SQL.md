# SQL commands
## SELECT
Select * FROM table_name;
> displays the complete table of the database

## SELECT DISTINCT
SELECT COUNT(DISTINCT Country) FROM Customers;
> The distinct command merges values, that appear in the table more than once

## WHERE
SELECT Zeile1,Zeile2, FROM table_name WHERE Zustand;
zB: `WHERE Country="Austria";`
> Zustände(Conditions) can be used with AND,OR,NOT. 

## ORDER BY
With this command it is possible to sort a column by a value. The order can either be ascending or descenting. default is ascending.
```SELECT * FROM table_name
ORDER BY Country DESC;
```
## INSERT INTO
With INSERT INTO you can insert values into column of the table.
```
INSERT INTO table_name(column1,column2)
VALUES (value1,value2);
```
