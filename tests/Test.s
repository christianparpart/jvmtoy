Classfile /home/trapni/projects/jvmtoy/tests/Test.class
  Last modified Nov 1, 2013; size 729 bytes
  MD5 checksum 61017d36201e23c272f2c92a9c05c2e4
  Compiled from "Test.java"
public class Test
  SourceFile: "Test.java"
  minor version: 0
  major version: 51
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #10.#23        //  java/lang/Object."<init>":()V
   #2 = Fieldref           #24.#25        //  java/lang/System.out:Ljava/io/PrintStream;
   #3 = String             #26            //  Hello, World
   #4 = Methodref          #27.#28        //  java/io/PrintStream.println:(Ljava/lang/String;)V
   #5 = Class              #29            //  Test
   #6 = Methodref          #5.#23         //  Test."<init>":()V
   #7 = Methodref          #5.#30         //  Test.test:()V
   #8 = Methodref          #5.#31         //  Test.testfunc:(I)I
   #9 = Methodref          #27.#32        //  java/io/PrintStream.println:(I)V
  #10 = Class              #33            //  java/lang/Object
  #11 = Utf8               <init>
  #12 = Utf8               ()V
  #13 = Utf8               Code
  #14 = Utf8               LineNumberTable
  #15 = Utf8               main
  #16 = Utf8               ([Ljava/lang/String;)V
  #17 = Utf8               test
  #18 = Utf8               testfunc
  #19 = Utf8               (I)I
  #20 = Utf8               StackMapTable
  #21 = Utf8               SourceFile
  #22 = Utf8               Test.java
  #23 = NameAndType        #11:#12        //  "<init>":()V
  #24 = Class              #34            //  java/lang/System
  #25 = NameAndType        #35:#36        //  out:Ljava/io/PrintStream;
  #26 = Utf8               Hello, World
  #27 = Class              #37            //  java/io/PrintStream
  #28 = NameAndType        #38:#39        //  println:(Ljava/lang/String;)V
  #29 = Utf8               Test
  #30 = NameAndType        #17:#12        //  test:()V
  #31 = NameAndType        #18:#19        //  testfunc:(I)I
  #32 = NameAndType        #38:#40        //  println:(I)V
  #33 = Utf8               java/lang/Object
  #34 = Utf8               java/lang/System
  #35 = Utf8               out
  #36 = Utf8               Ljava/io/PrintStream;
  #37 = Utf8               java/io/PrintStream
  #38 = Utf8               println
  #39 = Utf8               (Ljava/lang/String;)V
  #40 = Utf8               (I)V
{
  public Test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 1: 0
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0       
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return        
      LineNumberTable:
        line 1: 0

  public static void main(java.lang.String[]);
    flags: ACC_PUBLIC, ACC_STATIC
    LineNumberTable:
      line 3: 0
      line 5: 8
      line 6: 16
      line 7: 20
    Code:
      stack=2, locals=2, args_size=1
         0: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
         3: ldc           #3                  // String Hello, World
         5: invokevirtual #4                  // Method java/io/PrintStream.println:(Ljava/lang/String;)V
         8: new           #5                  // class Test
        11: dup           
        12: invokespecial #6                  // Method "<init>":()V
        15: astore_1      
        16: aload_1       
        17: invokevirtual #7                  // Method test:()V
        20: return        
      LineNumberTable:
        line 3: 0
        line 5: 8
        line 6: 16
        line 7: 20

  public void test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 10: 0
      line 11: 7
      line 12: 14
    Code:
      stack=2, locals=2, args_size=1
         0: aload_0       
         1: bipush        42
         3: invokevirtual #8                  // Method testfunc:(I)I
         6: istore_1      
         7: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
        10: iload_1       
        11: invokevirtual #9                  // Method java/io/PrintStream.println:(I)V
        14: return        
      LineNumberTable:
        line 10: 0
        line 11: 7
        line 12: 14

  public int testfunc(int);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 15: 0
      line 16: 2
      line 17: 9
      line 18: 18
      line 19: 25
      line 20: 29
      line 17: 32
      line 23: 38
      line 16: 45
      line 25: 51
    Code:
      stack=2, locals=5, args_size=2
         0: iconst_m1     
         1: istore_2      
         2: iconst_0      
         3: istore_3      
         4: iload_3       
         5: iload_1       
         6: if_icmpge     51
         9: iconst_2      
        10: istore        4
        12: iload         4
        14: iload_3       
        15: if_icmpge     38
        18: iload_3       
        19: iload         4
        21: irem          
        22: ifne          32
        25: iload_2       
        26: iload_3       
        27: iadd          
        28: istore_2      
        29: goto          38
        32: iinc          4, 1
        35: goto          12
        38: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
        41: iload_3       
        42: invokevirtual #9                  // Method java/io/PrintStream.println:(I)V
        45: iinc          3, 1
        48: goto          4
        51: iload_2       
        52: ireturn       
      LineNumberTable:
        line 15: 0
        line 16: 2
        line 17: 9
        line 18: 18
        line 19: 25
        line 20: 29
        line 17: 32
        line 23: 38
        line 16: 45
        line 25: 51
      StackMapTable: number_of_entries = 5
           frame_type = 253 /* append */
             offset_delta = 4
        locals = [ int, int ]
           frame_type = 252 /* append */
             offset_delta = 7
        locals = [ int ]
           frame_type = 19 /* same */
           frame_type = 250 /* chop */
          offset_delta = 5
           frame_type = 250 /* chop */
          offset_delta = 12

}
