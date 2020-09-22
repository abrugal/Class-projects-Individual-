/*Written by Esteban Brugal*/

/*This program adds students and faculty to list. You can also pull up each student
and faculty to check them.
Rank of faculty must either be professor or adjunct. And departments allowed are Mathematics,
physics, or engineering*/

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.lang.Character;

public class Project3 {

    static final double CREDIT_HOUR = 236.45;
    static final int ADMIN_FEE = 52;
    static final int MAX_SIZE = 100;

    public static void main(String[] args){
        ArrayList<Person> list = new ArrayList<Person>();
        Scanner scan = new Scanner(System.in);
        String option;
        System.out.println("\t\t\t\t\t\t\tWelcome to my Personal Management Program\n");
        do{
            printOptions();
            option = scan.nextLine();

            switch(option){
                case "1":
                    if(list.size() != MAX_SIZE)
                        addFaculty(list, scan);
                    else
                        System.out.println("List is already full. Can't add more faculty.\n");
                    break;
                case "2":
                    System.out.print("\n\n");
                    if(list.size() != MAX_SIZE)
                        addStudent(list, scan);
                    else
                        System.out.println("List is already full. Can't add more students.\n");
                    break;
                case "3":
                    System.out.print("\n\n\tEnter the student's id: ");
                    Person stud = findStudent(list, scan.nextLine());
                    if(stud != null)
                        stud.print();
                    else
                        System.out.println("Sorry-student not found!\n\n");
                    break;
                case "4":
                    System.out.print("\n\n\tEnter the faculty's id: ");
                    String find = scan.nextLine();
                    Person fac = findFaculty(list, find);
                    if(fac != null)
                        fac.print();
                    else
                        System.out.println("\tSorry " + find + " doesn't exist\n\n");
                    break;
                case "5":
                    String c = "";
                    System.out.print("\n\n");
                    while(!(c.equalsIgnoreCase("y") || c.equalsIgnoreCase("n"))) {
                        System.out.println("Would you like to create the report? (Y/N): ");
                        c = scan.nextLine();
                        if (c.equalsIgnoreCase("y")) {
                            reportCreation(list, scan);
                            System.out.println("Goodbye!");
                        } else if (c.equalsIgnoreCase("n"))
                            System.out.println("Goodbye!");
                        else
                            System.out.println("Please enter an actual answer.");
                    }
                    break;
                default:
                    System.out.print("\n\n");
                    System.out.println("Invalid entry- please try again\n\n");
            }
        }while(!(option.equals("5")));
    }

    static abstract class Person{
        protected String name;
        protected String id;

        public void setName(String name){
            this.name = name;
        }

        public void setId(String id){
            this.id = id;
        }

        public String getName(){
            return name;
        }

        public String getId(){
            return id;
        }

        abstract void print();

        abstract int type();

    }

    static class Student extends Person{
        private double gpa;
        private int credit;

        public Student(){
            gpa = -1;
            credit = -1;
            name = "";
            id = "";
        }

        public Student(String name, String id, double gpa, int credit){
            this.name = name;
            this.id = id;
            this.gpa = gpa;
            this.credit = credit;
        }

        public void setCredit(int credit){
            this.credit = credit;
        }

        public void setGpa(double gpa){
            this.gpa = gpa;
        }

        public int getCredit(){
            return credit;
        }

        public double getGpa(){
            return gpa;
        }

        public void print(){
            System.out.println("\tHere is the tuition invoice for " + name + " :\n");
            System.out.println("\t---------------------------------------------------------------------------");
            System.out.println("\t" + name + "\t\t\t" + id);
            System.out.print("\tCredit Hours:" + credit);
            System.out.println(" ($" + CREDIT_HOUR + "/credit hour)");
            System.out.println("\tFees: $" + ADMIN_FEE + "\n");
            System.out.printf("\tTotal payment: $%.2f", payment());
            System.out.printf("\t\t\t\t($%.2f discount applied)\n", discount());
            System.out.println("\t---------------------------------------------------------------------------\n");
        }

        public int type() { return 0; }

        private double discount(){
            if(gpa > 3.85 || Math.abs(gpa - 3.85) < 0.0001){
                return (CREDIT_HOUR * credit + ADMIN_FEE) * 0.25;
            }
            return 0;
        }

        private double payment(){
            return (CREDIT_HOUR * credit) - discount() + ADMIN_FEE;
        }

    }

    static class Faculty extends Person{
        private String department, rank;

        public Faculty(){
            name = "";
            id = "";
            department = "";
            rank = "";
        }

        public Faculty(String name, String id, String department, String rank){
            this.name = name;
            this.id = id;
            this.department = department;
            this.rank = rank;
        }

        public void setDepartment(String department){
            this.department = department;
        }

        public void setRank(String rank){
            this.rank = rank;
        }

        public String getDepartment(){
            return department;
        }

        public String getRank(){
            return rank;
        }

        public void print(){
            System.out.print("Faculty found:\n");
            System.out.println("\t---------------------------------------------------------------------------");
            System.out.println("\t" + name);
            System.out.println("\t" + department + " Department, " + rank);
            System.out.println("\t---------------------------------------------------------------------------");
        }

        public int type() { return 1; }

    }

    public static Person findStudent(ArrayList<Person> list, String id){
        int n = list.size();
        for(int i = 0; i < n; i++){
            String ID = list.get(i).getId();
            if(ID.equals(id) && list.get(i).type() == 0){
                return list.get(i);
            }
        }
        return null;
    }

    public static Person findFaculty(ArrayList<Person> list, String id){
        int n = list.size();
        for(int i = 0; i < n; i++){
            String ID = list.get(i).getId();
            if(ID.equals(id) && list.get(i).type() == 1){
                return list.get(i);
            }
        }
        return null;
    }

    public static void printOptions(){
        System.out.println("Choose one of the options:\n");
        System.out.println("1- Add a new Faculty member");
        System.out.println("2- Add a new Student");
        System.out.println("3- Print tuition invoice for a student");
        System.out.println("4- Print information of a faculty");
        System.out.println("5- Exit Program\n");
        System.out.print("\tEnter your selection: ");
    }

    public static void addFaculty(ArrayList<Person> list, Scanner scan){
        String id;
        Faculty fac = new Faculty();
        String rank, department;
        System.out.println("\nEnter the faculty's info:\n");
        System.out.print("\t\tName of the Faculty: ");
        fac.setName(scan.nextLine());
        System.out.print("\n\t\tID: ");
        id = scan.nextLine();
        if(idInput(id))
            fac.setId(id);
        else {
            System.out.print("\n\tSorry Invalid id format-It has to be LetterLetterDigitDigitDigitDigit\n\n");
            return;
        }
        System.out.print("\n\t\tRank: ");
        rank = scan.nextLine();

        while(!(rank.equalsIgnoreCase("professor") || rank.equalsIgnoreCase("adjunct"))){
            System.out.print("\t\t\tSorry, entered rank (" + rank + ") is invalid\n");
            System.out.print("\t\tRank: ");
            rank = scan.nextLine();
        }

        fac.setRank(rank.substring(0,1).toUpperCase() + rank.substring(1).toLowerCase());
        System.out.print("\n\t\tDepartment: ");
        department = scan.nextLine();

        while(!(department.equalsIgnoreCase("mathematics") || department.equalsIgnoreCase("physics") || department.equalsIgnoreCase("engineering"))) {
            System.out.print("\t\t\tSorry, entered department (" + department + ") is invalid\n");
            System.out.print("\t\tDepartment: ");
            department = scan.nextLine();
        }

        fac.setDepartment(department.substring(0,1).toUpperCase() + department.substring(1).toLowerCase());
        list.add(fac);
        System.out.println("\nThanks!\n\n");
    }

    public static void addStudent(ArrayList<Person> list, Scanner scan){
        String id;
        Student stud = new Student();
        System.out.println("Enter the student's info:\n");
        System.out.print("\t\tName of Student: ");
        stud.setName(scan.nextLine());
        System.out.print("\n\t\tID: ");
        id = scan.nextLine();
        if(idInput(id))
            stud.setId(id);
        else {
            System.out.print("\n\tSorry Invalid id format-It has to be LetterLetterDigitDigitDigitDigit\n\n");
            return;
        }
        stud.setId(id);
        System.out.print("\n\t\tGpa: ");
        try{
            Double gpa = scan.nextDouble();
            stud.setGpa(gpa);
            System.out.print("\n\t\tCredit hours: ");
            int credit = scan.nextInt();
            stud.setCredit(credit);
            list.add(stud);
            scan.nextLine();
            System.out.println("\nThanks!\n\n");
        }catch(InputMismatchException e){
            System.out.println("\nError entering information. Please try again.");
            scan.nextLine();
        }
    }

    public static boolean idInput(String id){
        int letter = 0, num = 0;
        for(int i = 0; i < id.length(); i++) {
            if (Character.isLetter(id.charAt(i)))
                letter++;
            else if (Character.isDigit(id.charAt(i)))
                num++;
        }
        return letter == 2 && num == 4;
    }

    public static String getCurrentDate(){
        String formattedDate;
        Date currentDate = new Date();
        String date = currentDate.toString();
        Scanner scan = new Scanner(date);
        scan.next();
        String month = scan.next();
        //System.out.print();
        formattedDate = convertMonthToInt(month) + "/";
        String day = scan.next();
        formattedDate += day + "/2020";             //we assume it's the year 2020
        return formattedDate;
    }

    public static String convertMonthToInt(String month){
        if(month.substring(0,3).equalsIgnoreCase("jan"))
            return "1";
        else if(month.substring(0,3).equalsIgnoreCase("feb"))
            return "2";
        else if(month.substring(0,3).equalsIgnoreCase("mar"))
            return "3";
        else if(month.substring(0,3).equalsIgnoreCase("apr"))
            return "4";
        else if(month.substring(0,3).equalsIgnoreCase("may"))
            return "5";
        else if(month.substring(0,3).equalsIgnoreCase("jun"))
            return "6";
        else if(month.substring(0,3).equalsIgnoreCase("jul"))
            return "7";
        else if(month.substring(0,3).equalsIgnoreCase("aug"))
            return "8";
        else if(month.substring(0,3).equalsIgnoreCase("sep"))
            return "9";
        else if(month.substring(0,3).equalsIgnoreCase("oct"))
            return "10";
        else if(month.substring(0,3).equalsIgnoreCase("nov"))
            return "11";
        else if(month.substring(0,3).equalsIgnoreCase("dec"))
            return "12";
        return "ERROR";
    }

    public static void reportCreation(ArrayList<Person> list, Scanner scan) {
        try {
            File report = new File("report.dat");
            if (report.createNewFile()) {
                System.out.println("Your file has been created!");
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred creating file.");
        }

        try {
            FileWriter writer = new FileWriter("report.dat");
            writer.write("\t\tReport created on " + getCurrentDate());
            writer.write("\n\t\t***********************");
            writer.write("\n\nFaculty Members (Sorted by Department)");
            writer.write("\n--------------------------------------------------");
            writeFaculty(writer, list);
            writer.write("\n\n\n\n\nStudents\n-----------");
            writeStudent(writer, list);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred writing to file.");
        }
    }

    public static void writeFaculty(FileWriter writer, ArrayList<Person> list){
        int count = 1;
        Faculty fac = new Faculty();
        for(int i = 0; i < list.size(); i++){
            if(list.get(i).type() == 1 && ((Faculty) list.get(i)).getDepartment().equalsIgnoreCase("engineering")) {
                fac = (Faculty) list.get(i);
                try{
                    writer.write("\n\t"+count + ". " + fac.getName());
                    writer.write("\n\tID: " + fac.getId());
                    writer.write("\n\t" + fac.getRank() + "," + fac.getDepartment());
                    writer.write("\n");
                    count++;
                } catch (IOException e) {
                    System.out.println("An error occurred writing to file.");
                }
            }
        }
        for(int i = 0; i < list.size(); i++){
            if(list.get(i).type() == 1 && ((Faculty) list.get(i)).getDepartment().equalsIgnoreCase("mathematics")) {
                fac = (Faculty) list.get(i);
                try{
                    writer.write("\n\t"+count + ". " + fac.getName());
                    writer.write("\n\tID: " + fac.getId());
                    writer.write("\n\t" + fac.getRank() + "," + fac.getDepartment());
                    writer.write("\n");
                    count++;
                } catch (IOException e) {
                    System.out.println("An error occurred writing to file.");
                }
            }
        }
        for(int i = 0; i < list.size(); i++){
            if(list.get(i).type() == 1 && ((Faculty) list.get(i)).getDepartment().equalsIgnoreCase("physics")) {
                fac = (Faculty) list.get(i);
                try{
                    writer.write("\n\t"+count + ". " + fac.getName());
                    writer.write("\n\tID: " + fac.getId());
                    writer.write("\n\t" + fac.getRank() + "," + fac.getDepartment());
                    writer.write("\n");
                    count++;
                } catch (IOException e) {
                    System.out.println("An error occurred writing to file.");
                }
            }
        }
    }

    public static void writeStudent(FileWriter writer, ArrayList<Person> list){
        int count = 1;
        Student stud = new Student();
        for(int i = 0; i < list.size(); i++){
            if(list.get(i).type() == 0){
                stud = (Student) list.get(i);
                try{
                    writer.write("\n\t"+count + ". " + stud.getName());
                    writer.write("\n\tID: " + stud.getId());
                    writer.write("\n\tGpa: " + stud.getGpa());
                    writer.write("\n\tCredit hours: " + stud.getCredit());
                    writer.write("\n");
                    count++;
                } catch (IOException e) {
                    System.out.println("An error occurred writing to file.");
                }
            }
        }
    }


}



