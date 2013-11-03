Classfile /home/trapni/projects/jvmtoy/tests/Test.class
  Last modified Nov 3, 2013; size 1101 bytes
  MD5 checksum bb3e24f03cf020f9a6712fceca3db3a5
  Compiled from "Test.java"
public class Test
  SourceFile: "Test.java"
  minor version: 0
  major version: 51
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #19.#42        //  java/lang/Object."<init>":()V
   #2 = Fieldref           #6.#43         //  Test.i:I
   #3 = Fieldref           #44.#45        //  java/lang/System.out:Ljava/io/PrintStream;
   #4 = String             #46            //  Hello, World
   #5 = Methodref          #47.#48        //  java/io/PrintStream.println:(Ljava/lang/String;)V
   #6 = Class              #49            //  Test
   #7 = Methodref          #6.#42         //  Test."<init>":()V
   #8 = Methodref          #6.#50         //  Test.test:()V
   #9 = Long               -889275714l
  #11 = Methodref          #6.#51         //  Test.testfunc:(J)J
  #12 = Methodref          #47.#52        //  java/io/PrintStream.println:(J)V
  #13 = Long               -1l
  #15 = Long               2l
  #17 = String             #34            //  fnord
  #18 = Methodref          #44.#53        //  java/lang/System.loadLibrary:(Ljava/lang/String;)V
  #19 = Class              #54            //  java/lang/Object
  #20 = Utf8               i
  #21 = Utf8               I
  #22 = Utf8               <init>
  #23 = Utf8               ()V
  #24 = Utf8               Code
  #25 = Utf8               LineNumberTable
  #26 = Utf8               main
  #27 = Utf8               ([Ljava/lang/String;)V
  #28 = Utf8               addToI
  #29 = Utf8               (I)V
  #30 = Utf8               test
  #31 = Utf8               testfunc
  #32 = Utf8               (J)J
  #33 = Utf8               StackMapTable
  #34 = Utf8               fnord
  #35 = Utf8               (ILjava/lang/String;)V
  #36 = Utf8               fnord2
  #37 = Utf8               ()Ljava/lang/String;
  #38 = Utf8               (I)Ljava/lang/String;
  #39 = Utf8               <clinit>
  #40 = Utf8               SourceFile
  #41 = Utf8               Test.java
  #42 = NameAndType        #22:#23        //  "<init>":()V
  #43 = NameAndType        #20:#21        //  i:I
  #44 = Class              #55            //  java/lang/System
  #45 = NameAndType        #56:#57        //  out:Ljava/io/PrintStream;
  #46 = Utf8               Hello, World
  #47 = Class              #58            //  java/io/PrintStream
  #48 = NameAndType        #59:#60        //  println:(Ljava/lang/String;)V
  #49 = Utf8               Test
  #50 = NameAndType        #30:#23        //  test:()V
  #51 = NameAndType        #31:#32        //  testfunc:(J)J
  #52 = NameAndType        #59:#61        //  println:(J)V
  #53 = NameAndType        #62:#60        //  loadLibrary:(Ljava/lang/String;)V
  #54 = Utf8               java/lang/Object
  #55 = Utf8               java/lang/System
  #56 = Utf8               out
  #57 = Utf8               Ljava/io/PrintStream;
  #58 = Utf8               java/io/PrintStream
  #59 = Utf8               println
  #60 = Utf8               (Ljava/lang/String;)V
  #61 = Utf8               (J)V
  #62 = Utf8               loadLibrary
{
  public int i;
    flags: ACC_PUBLIC


  public Test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 2: 0
      line 5: 4
      line 3: 10
    Code:
      stack=2, locals=1, args_size=1
         0: aload_0       
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: aload_0       
         5: bipush        42
         7: putfield      #2                  // Field i:I
        10: return        
      LineNumberTable:
        line 2: 0
        line 5: 4
        line 3: 10

  public static void main(java.lang.String[]);
    flags: ACC_PUBLIC, ACC_STATIC
    LineNumberTable:
      line 8: 0
      line 10: 8
      line 11: 16
      line 12: 20
    Code:
      stack=2, locals=2, args_size=1
         0: getstatic     #3                  // Field java/lang/System.out:Ljava/io/PrintStream;
         3: ldc           #4                  // String Hello, World
         5: invokevirtual #5                  // Method java/io/PrintStream.println:(Ljava/lang/String;)V
         8: new           #6                  // class Test
        11: dup           
        12: invokespecial #7                  // Method "<init>":()V
        15: astore_1      
        16: aload_1       
        17: invokevirtual #8                  // Method test:()V
        20: return        
      LineNumberTable:
        line 8: 0
        line 10: 8
        line 11: 16
        line 12: 20

  public void addToI(int);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 15: 0
      line 16: 10
    Code:
      stack=3, locals=2, args_size=2
         0: aload_0       
         1: dup           
         2: getfield      #2                  // Field i:I
         5: iload_1       
         6: iadd          
         7: putfield      #2                  // Field i:I
        10: return        
      LineNumberTable:
        line 15: 0
        line 16: 10

  public void test();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 19: 0
      line 20: 8
      line 21: 15
    Code:
      stack=3, locals=3, args_size=1
         0: aload_0       
         1: ldc2_w        #9                  // long -889275714l
         4: invokevirtual #11                 // Method testfunc:(J)J
         7: lstore_1      
         8: getstatic     #3                  // Field java/lang/System.out:Ljava/io/PrintStream;
        11: lload_1       
        12: invokevirtual #12                 // Method java/io/PrintStream.println:(J)V
        15: return        
      LineNumberTable:
        line 19: 0
        line 20: 8
        line 21: 15

  public long testfunc(long);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 24: 0
      line 25: 4
      line 26: 14
      line 27: 27
      line 28: 37
      line 29: 42
      line 26: 45
      line 32: 54
      line 25: 62
      line 34: 71
    Code:
      stack=4, locals=9, args_size=2
         0: ldc2_w        #13                 // long -1l
         3: lstore_3      
         4: lconst_0      
         5: lstore        5
         7: lload         5
         9: lload_1       
        10: lcmp          
        11: ifge          71
        14: ldc2_w        #15                 // long 2l
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
        54: getstatic     #3                  // Field java/lang/System.out:Ljava/io/PrintStream;
        57: lload         5
        59: invokevirtual #12                 // Method java/io/PrintStream.println:(J)V
        62: lload         5
        64: lconst_1      
        65: ladd          
        66: lstore        5
        68: goto          7
        71: lload_3       
        72: lreturn       
      LineNumberTable:
        line 24: 0
        line 25: 4
        line 26: 14
        line 27: 27
        line 28: 37
        line 29: 42
        line 26: 45
        line 32: 54
        line 25: 62
        line 34: 71
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
      line 44: 0
      line 45: 5
    Code:
      stack=1, locals=0, args_size=0
         0: ldc           #17                 // String fnord
         2: invokestatic  #18                 // Method java/lang/System.loadLibrary:(Ljava/lang/String;)V
         5: return        
      LineNumberTable:
        line 44: 0
        line 45: 5
}
