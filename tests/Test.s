Classfile /home/trapni/projects/jvmtoy/tests/Test.class
  Last modified Nov 2, 2013; size 1003 bytes
  MD5 checksum ce9ea195ebe10cca246d4f5f9ff067a6
  Compiled from "Test.java"
public class Test
  SourceFile: "Test.java"
  minor version: 0
  major version: 51
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #18.#38        //  java/lang/Object."<init>":()V
   #2 = Fieldref           #39.#40        //  java/lang/System.out:Ljava/io/PrintStream;
   #3 = String             #41            //  Hello, World
   #4 = Methodref          #42.#43        //  java/io/PrintStream.println:(Ljava/lang/String;)V
   #5 = Class              #44            //  Test
   #6 = Methodref          #5.#38         //  Test."<init>":()V
   #7 = Methodref          #5.#45         //  Test.test:()V
   #8 = Long               -889275714l
  #10 = Methodref          #5.#46         //  Test.testfunc:(J)J
  #11 = Methodref          #42.#47        //  java/io/PrintStream.println:(J)V
  #12 = Long               -1l
  #14 = Long               2l
  #16 = String             #29            //  fnord
  #17 = Methodref          #39.#48        //  java/lang/System.loadLibrary:(Ljava/lang/String;)V
  #18 = Class              #49            //  java/lang/Object
  #19 = Utf8               <init>
  #20 = Utf8               ()V
  #21 = Utf8               Code
  #22 = Utf8               LineNumberTable
  #23 = Utf8               main
  #24 = Utf8               ([Ljava/lang/String;)V
  #25 = Utf8               test
  #26 = Utf8               testfunc
  #27 = Utf8               (J)J
  #28 = Utf8               StackMapTable
  #29 = Utf8               fnord
  #30 = Utf8               (I)V
  #31 = Utf8               (ILjava/lang/String;)V
  #32 = Utf8               fnord2
  #33 = Utf8               ()Ljava/lang/String;
  #34 = Utf8               (I)Ljava/lang/String;
  #35 = Utf8               <clinit>
  #36 = Utf8               SourceFile
  #37 = Utf8               Test.java
  #38 = NameAndType        #19:#20        //  "<init>":()V
  #39 = Class              #50            //  java/lang/System
  #40 = NameAndType        #51:#52        //  out:Ljava/io/PrintStream;
  #41 = Utf8               Hello, World
  #42 = Class              #53            //  java/io/PrintStream
  #43 = NameAndType        #54:#55        //  println:(Ljava/lang/String;)V
  #44 = Utf8               Test
  #45 = NameAndType        #25:#20        //  test:()V
  #46 = NameAndType        #26:#27        //  testfunc:(J)J
  #47 = NameAndType        #54:#56        //  println:(J)V
  #48 = NameAndType        #57:#55        //  loadLibrary:(Ljava/lang/String;)V
  #49 = Utf8               java/lang/Object
  #50 = Utf8               java/lang/System
  #51 = Utf8               out
  #52 = Utf8               Ljava/io/PrintStream;
  #53 = Utf8               java/io/PrintStream
  #54 = Utf8               println
  #55 = Utf8               (Ljava/lang/String;)V
  #56 = Utf8               (J)V
  #57 = Utf8               loadLibrary
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
      line 14: 8
      line 15: 15
    Code:
      stack=3, locals=3, args_size=1
         0: aload_0       
         1: ldc2_w        #8                  // long -889275714l
         4: invokevirtual #10                 // Method testfunc:(J)J
         7: lstore_1      
         8: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
        11: lload_1       
        12: invokevirtual #11                 // Method java/io/PrintStream.println:(J)V
        15: return        
      LineNumberTable:
        line 13: 0
        line 14: 8
        line 15: 15

  public long testfunc(long);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 18: 0
      line 19: 4
      line 20: 14
      line 21: 27
      line 22: 37
      line 23: 42
      line 20: 45
      line 26: 54
      line 19: 62
      line 28: 71
    Code:
      stack=4, locals=9, args_size=2
         0: ldc2_w        #12                 // long -1l
         3: lstore_3      
         4: lconst_0      
         5: lstore        5
         7: lload         5
         9: lload_1       
        10: lcmp          
        11: ifge          71
        14: ldc2_w        #14                 // long 2l
        17: lstore        7
        19: lload         7
        21: lload         5
        23: lcmp          
        24: ifge          54
        27: lload         5
        29: lload         7
        31: lrem          
        32: lconst_0      
        33: lcmp          
        34: ifne          45
        37: lload_3       
        38: lload         5
        40: ladd          
        41: lstore_3      
        42: goto          54
        45: lload         7
        47: lconst_1      
        48: ladd          
        49: lstore        7
        51: goto          19
        54: getstatic     #2                  // Field java/lang/System.out:Ljava/io/PrintStream;
        57: lload         5
        59: invokevirtual #11                 // Method java/io/PrintStream.println:(J)V
        62: lload         5
        64: lconst_1      
        65: ladd          
        66: lstore        5
        68: goto          7
        71: lload_3       
        72: lreturn       
      LineNumberTable:
        line 18: 0
        line 19: 4
        line 20: 14
        line 21: 27
        line 22: 37
        line 23: 42
        line 20: 45
        line 26: 54
        line 19: 62
        line 28: 71
      StackMapTable: number_of_entries = 5
           frame_type = 253 /* append */
             offset_delta = 7
        locals = [ long, long ]
           frame_type = 252 /* append */
             offset_delta = 11
        locals = [ long ]
           frame_type = 25 /* same */
           frame_type = 250 /* chop */
          offset_delta = 8
           frame_type = 250 /* chop */
          offset_delta = 16


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
         0: ldc           #16                 // String fnord
         2: invokestatic  #17                 // Method java/lang/System.loadLibrary:(Ljava/lang/String;)V
         5: return        
      LineNumberTable:
        line 38: 0
        line 39: 5
}
