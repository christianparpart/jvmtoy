Classfile /home/trapni/projects/jvmtoy/tests/Test.class
  Last modified Nov 1, 2013; size 948 bytes
  MD5 checksum 3cc551b2e1869b4424d36c93e2096041
  Compiled from "Test.java"
public class Test
  SourceFile: "Test.java"
  minor version: 0
  major version: 51
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #12.#32        //  java/lang/Object."<init>":()V
   #2 = Fieldref           #33.#34        //  java/lang/System.out:Ljava/io/PrintStream;
   #3 = String             #35            //  Hello, World
   #4 = Methodref          #36.#37        //  java/io/PrintStream.println:(Ljava/lang/String;)V
   #5 = Class              #38            //  Test
   #6 = Methodref          #5.#32         //  Test."<init>":()V
   #7 = Methodref          #5.#39         //  Test.test:()V
   #8 = Methodref          #5.#40         //  Test.testfunc:(I)I
   #9 = Methodref          #36.#41        //  java/io/PrintStream.println:(I)V
  #10 = String             #23            //  fnord
  #11 = Methodref          #33.#42        //  java/lang/System.loadLibrary:(Ljava/lang/String;)V
  #12 = Class              #43            //  java/lang/Object
  #13 = Utf8               <init>
  #14 = Utf8               ()V
  #15 = Utf8               Code
  #16 = Utf8               LineNumberTable
  #17 = Utf8               main
  #18 = Utf8               ([Ljava/lang/String;)V
  #19 = Utf8               test
  #20 = Utf8               testfunc
  #21 = Utf8               (I)I
  #22 = Utf8               StackMapTable
  #23 = Utf8               fnord
  #24 = Utf8               (I)V
  #25 = Utf8               (ILjava/lang/String;)V
  #26 = Utf8               fnord2
  #27 = Utf8               ()Ljava/lang/String;
  #28 = Utf8               (I)Ljava/lang/String;
  #29 = Utf8               <clinit>
  #30 = Utf8               SourceFile
  #31 = Utf8               Test.java
  #32 = NameAndType        #13:#14        //  "<init>":()V
  #33 = Class              #44            //  java/lang/System
  #34 = NameAndType        #45:#46        //  out:Ljava/io/PrintStream;
  #35 = Utf8               Hello, World
  #36 = Class              #47            //  java/io/PrintStream
  #37 = NameAndType        #48:#49        //  println:(Ljava/lang/String;)V
  #38 = Utf8               Test
  #39 = NameAndType        #19:#14        //  test:()V
  #40 = NameAndType        #20:#21        //  testfunc:(I)I
  #41 = NameAndType        #48:#24        //  println:(I)V
  #42 = NameAndType        #50:#49        //  loadLibrary:(Ljava/lang/String;)V
  #43 = Utf8               java/lang/Object
  #44 = Utf8               java/lang/System
  #45 = Utf8               out
  #46 = Utf8               Ljava/io/PrintStream;
  #47 = Utf8               java/io/PrintStream
  #48 = Utf8               println
  #49 = Utf8               (Ljava/lang/String;)V
  #50 = Utf8               loadLibrary
{
  public Test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 2: 0
      line 3: 4
    Code:
      stack=1, locals=1, args_size=1
         0: aload_0       
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: return        
      LineNumberTable:
        line 2: 0
        line 3: 4

  public static void main(java.lang.String[]);
    flags: ACC_PUBLIC, ACC_STATIC
    LineNumberTable:
      line 6: 0
      line 8: 8
      line 9: 16
      line 10: 20
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
        line 6: 0
        line 8: 8
        line 9: 16
        line 10: 20

  public void test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 13: 0
      line 14: 7
      line 15: 14
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
        line 13: 0
        line 14: 7
        line 15: 14

  public int testfunc(int);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 18: 0
      line 19: 2
      line 20: 9
      line 21: 18
      line 22: 25
      line 23: 29
      line 20: 32
      line 26: 38
      line 19: 45
      line 28: 51
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
        line 18: 0
        line 19: 2
        line 20: 9
        line 21: 18
        line 22: 25
        line 23: 29
        line 20: 32
        line 26: 38
        line 19: 45
        line 28: 51
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


  public native void fnord();
    flags: ACC_PUBLIC, ACC_NATIVE

  public native void fnord(int);
    flags: ACC_PUBLIC, ACC_NATIVE

  public native void fnord(int, java.lang.String);
    flags: ACC_PUBLIC, ACC_NATIVE

  public native java.lang.String fnord2();
    flags: ACC_PUBLIC, ACC_NATIVE

  public native java.lang.String fnord2(int);
    flags: ACC_PUBLIC, ACC_NATIVE

  static {};
    flags: ACC_STATIC
    LineNumberTable:
      line 38: 0
      line 39: 5
    Code:
      stack=1, locals=0, args_size=0
         0: ldc           #10                 // String fnord
         2: invokestatic  #11                 // Method java/lang/System.loadLibrary:(Ljava/lang/String;)V
         5: return        
      LineNumberTable:
        line 38: 0
        line 39: 5
}
