Classfile /home/trapni/projects/jvmtoy/tests/Template1.class
  Last modified Nov 8, 2013; size 1124 bytes
  MD5 checksum 37bccb741cbeb185560a95b2f9c51c93
  Compiled from "Template1.java"
public class Template1<T extends java.lang.Object> extends java.lang.Object
  Signature: #34                          // <T:Ljava/lang/Object;>Ljava/lang/Object;
  SourceFile: "Template1.java"
  minor version: 0
  major version: 51
  flags: ACC_PUBLIC, ACC_SUPER
Constant pool:
   #1 = Methodref          #19.#37        //  java/lang/Object."<init>":()V
   #2 = Fieldref           #10.#38        //  Template1.first:Ljava/lang/Object;
   #3 = Fieldref           #10.#39        //  Template1.second:Ljava/lang/Object;
   #4 = Class              #40            //  java/lang/StringBuilder
   #5 = Methodref          #4.#37         //  java/lang/StringBuilder."<init>":()V
   #6 = Methodref          #4.#41         //  java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
   #7 = String             #42            //  , 
   #8 = Methodref          #4.#43         //  java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
   #9 = Methodref          #4.#44         //  java/lang/StringBuilder.toString:()Ljava/lang/String;
  #10 = Class              #45            //  Template1
  #11 = String             #46            //  foo
  #12 = String             #47            //  bar
  #13 = Methodref          #10.#48        //  Template1."<init>":(Ljava/lang/Object;Ljava/lang/Object;)V
  #14 = Methodref          #49.#50        //  java/lang/Integer.valueOf:(I)Ljava/lang/Integer;
  #15 = Fieldref           #51.#52        //  java/lang/System.out:Ljava/io/PrintStream;
  #16 = String             #53            //  s: 
  #17 = Methodref          #54.#55        //  java/io/PrintStream.println:(Ljava/lang/String;)V
  #18 = String             #56            //  i: 
  #19 = Class              #57            //  java/lang/Object
  #20 = Utf8               first
  #21 = Utf8               Ljava/lang/Object;
  #22 = Utf8               Signature
  #23 = Utf8               TT;
  #24 = Utf8               second
  #25 = Utf8               <init>
  #26 = Utf8               (Ljava/lang/Object;Ljava/lang/Object;)V
  #27 = Utf8               Code
  #28 = Utf8               LineNumberTable
  #29 = Utf8               (TT;TT;)V
  #30 = Utf8               toString
  #31 = Utf8               ()Ljava/lang/String;
  #32 = Utf8               main
  #33 = Utf8               ([Ljava/lang/String;)V
  #34 = Utf8               <T:Ljava/lang/Object;>Ljava/lang/Object;
  #35 = Utf8               SourceFile
  #36 = Utf8               Template1.java
  #37 = NameAndType        #25:#58        //  "<init>":()V
  #38 = NameAndType        #20:#21        //  first:Ljava/lang/Object;
  #39 = NameAndType        #24:#21        //  second:Ljava/lang/Object;
  #40 = Utf8               java/lang/StringBuilder
  #41 = NameAndType        #59:#60        //  append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
  #42 = Utf8               , 
  #43 = NameAndType        #59:#61        //  append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
  #44 = NameAndType        #30:#31        //  toString:()Ljava/lang/String;
  #45 = Utf8               Template1
  #46 = Utf8               foo
  #47 = Utf8               bar
  #48 = NameAndType        #25:#26        //  "<init>":(Ljava/lang/Object;Ljava/lang/Object;)V
  #49 = Class              #62            //  java/lang/Integer
  #50 = NameAndType        #63:#64        //  valueOf:(I)Ljava/lang/Integer;
  #51 = Class              #65            //  java/lang/System
  #52 = NameAndType        #66:#67        //  out:Ljava/io/PrintStream;
  #53 = Utf8               s: 
  #54 = Class              #68            //  java/io/PrintStream
  #55 = NameAndType        #69:#70        //  println:(Ljava/lang/String;)V
  #56 = Utf8               i: 
  #57 = Utf8               java/lang/Object
  #58 = Utf8               ()V
  #59 = Utf8               append
  #60 = Utf8               (Ljava/lang/Object;)Ljava/lang/StringBuilder;
  #61 = Utf8               (Ljava/lang/String;)Ljava/lang/StringBuilder;
  #62 = Utf8               java/lang/Integer
  #63 = Utf8               valueOf
  #64 = Utf8               (I)Ljava/lang/Integer;
  #65 = Utf8               java/lang/System
  #66 = Utf8               out
  #67 = Utf8               Ljava/io/PrintStream;
  #68 = Utf8               java/io/PrintStream
  #69 = Utf8               println
  #70 = Utf8               (Ljava/lang/String;)V
{
  public Template1(T, T);
    flags: ACC_PUBLIC
    LineNumberTable:
      line 5: 0
      line 6: 4
      line 7: 9
      line 8: 14
    Code:
      stack=2, locals=3, args_size=3
         0: aload_0       
         1: invokespecial #1                  // Method java/lang/Object."<init>":()V
         4: aload_0       
         5: aload_1       
         6: putfield      #2                  // Field first:Ljava/lang/Object;
         9: aload_0       
        10: aload_2       
        11: putfield      #3                  // Field second:Ljava/lang/Object;
        14: return        
      LineNumberTable:
        line 5: 0
        line 6: 4
        line 7: 9
        line 8: 14
    Signature: #29                          // (TT;TT;)V

  public java.lang.String toString();
    flags: ACC_PUBLIC
    LineNumberTable:
      line 11: 0
    Code:
      stack=2, locals=1, args_size=1
         0: new           #4                  // class java/lang/StringBuilder
         3: dup           
         4: invokespecial #5                  // Method java/lang/StringBuilder."<init>":()V
         7: aload_0       
         8: getfield      #2                  // Field first:Ljava/lang/Object;
        11: invokevirtual #6                  // Method java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
        14: ldc           #7                  // String , 
        16: invokevirtual #8                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
        19: aload_0       
        20: getfield      #3                  // Field second:Ljava/lang/Object;
        23: invokevirtual #6                  // Method java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
        26: invokevirtual #9                  // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
        29: areturn       
      LineNumberTable:
        line 11: 0

  public static void main(java.lang.String[]);
    flags: ACC_PUBLIC, ACC_STATIC
    LineNumberTable:
      line 15: 0
      line 16: 12
      line 18: 28
      line 19: 53
      line 20: 78
    Code:
      stack=4, locals=3, args_size=1
         0: new           #10                 // class Template1
         3: dup           
         4: ldc           #11                 // String foo
         6: ldc           #12                 // String bar
         8: invokespecial #13                 // Method "<init>":(Ljava/lang/Object;Ljava/lang/Object;)V
        11: astore_1      
        12: new           #10                 // class Template1
        15: dup           
        16: iconst_4      
        17: invokestatic  #14                 // Method java/lang/Integer.valueOf:(I)Ljava/lang/Integer;
        20: iconst_2      
        21: invokestatic  #14                 // Method java/lang/Integer.valueOf:(I)Ljava/lang/Integer;
        24: invokespecial #13                 // Method "<init>":(Ljava/lang/Object;Ljava/lang/Object;)V
        27: astore_2      
        28: getstatic     #15                 // Field java/lang/System.out:Ljava/io/PrintStream;
        31: new           #4                  // class java/lang/StringBuilder
        34: dup           
        35: invokespecial #5                  // Method java/lang/StringBuilder."<init>":()V
        38: ldc           #16                 // String s: 
        40: invokevirtual #8                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
        43: aload_1       
        44: invokevirtual #6                  // Method java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
        47: invokevirtual #9                  // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
        50: invokevirtual #17                 // Method java/io/PrintStream.println:(Ljava/lang/String;)V
        53: getstatic     #15                 // Field java/lang/System.out:Ljava/io/PrintStream;
        56: new           #4                  // class java/lang/StringBuilder
        59: dup           
        60: invokespecial #5                  // Method java/lang/StringBuilder."<init>":()V
        63: ldc           #18                 // String i: 
        65: invokevirtual #8                  // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
        68: aload_2       
        69: invokevirtual #6                  // Method java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
        72: invokevirtual #9                  // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
        75: invokevirtual #17                 // Method java/io/PrintStream.println:(Ljava/lang/String;)V
        78: return        
      LineNumberTable:
        line 15: 0
        line 16: 12
        line 18: 28
        line 19: 53
        line 20: 78
}
