; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@2 = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@3 = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@4 = private unnamed_addr constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @Main() {
entry:
  %str = alloca [10 x i8]
  %array = alloca [5 x i32]
  %i = alloca i32
  %b = alloca i32
  %a = alloca i32
  store i32 3, i32* %a
  %0 = load [5 x i32], [5 x i32]* %array
  %1 = getelementptr [5 x i32], [5 x i32]* %array, i32 0, i32 2
  store i32 10, i32* %1
  %2 = load [10 x i8], [10 x i8]* %str
  %3 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 0
  store i8 0, i8* %3
  %4 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 1
  store i8 0, i8* %4
  %5 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 2
  store i8 0, i8* %5
  %6 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 3
  store i8 0, i8* %6
  %7 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 4
  store i8 0, i8* %7
  %8 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 5
  store i8 0, i8* %8
  %9 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 6
  store i8 0, i8* %9
  %10 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 7
  store i8 0, i8* %10
  %11 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 8
  store i8 0, i8* %11
  %12 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 9
  store i8 0, i8* %12
  %13 = load i32, i32* %a
  %cmptmpi = icmp eq i32 %13, 1
  %ifCond = icmp ne i1 %cmptmpi, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entry
  %14 = load i32, i32* %a
  %addtmpi = add i32 %14, 1
  store i32 %addtmpi, i32* %a
  br label %ifend

else:                                             ; preds = %entry
  %15 = load i32, i32* %a
  %cmptmpi1 = icmp eq i32 %15, 2
  %ifCond2 = icmp ne i1 %cmptmpi1, false
  br i1 %ifCond2, label %then3, label %else4

ifend:                                            ; preds = %ifend5, %then
  br label %cond

then3:                                            ; preds = %else
  %16 = load i32, i32* %a
  %addtmpi6 = add i32 %16, 2
  store i32 %addtmpi6, i32* %a
  br label %ifend5

else4:                                            ; preds = %else
  %17 = load i32, i32* %a
  %addtmpi7 = add i32 %17, 3
  store i32 %addtmpi7, i32* %b
  br label %ifend5

ifend5:                                           ; preds = %else4, %then3
  br label %ifend

cond:                                             ; preds = %loop, %ifend
  %18 = load i32, i32* %a
  %cmptmpi8 = icmp slt i32 %18, 10
  br i1 %cmptmpi8, label %loop, label %loopend

loop:                                             ; preds = %cond
  %19 = load i32, i32* %a
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 %19)
  %20 = load i32, i32* %b
  %addtmpi9 = add i32 %20, 3
  store i32 %addtmpi9, i32* %b
  %21 = load i32, i32* %a
  %addtmpi10 = add i32 %21, 1
  store i32 %addtmpi10, i32* %a
  br label %cond

loopend:                                          ; preds = %cond
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %forbody, %loopend
  %22 = load i32, i32* %i
  %cmptmpi11 = icmp slt i32 %22, 10
  br i1 %cmptmpi11, label %forbody, label %forend

forend:                                           ; preds = %forcond
  %23 = load i32, i32* %a
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @2, i32 0, i32 0), i32 %23)
  %24 = load i32, i32* %b
  %printf15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @3, i32 0, i32 0), i32 %24)
  %25 = load i32, i32* %a
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @4, i32 0, i32 0), i32 2)
  ret i32 0

forbody:                                          ; preds = %forcond
  %26 = load i32, i32* %i
  %printf12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 %26)
  %27 = load i32, i32* %i
  %addtmpi13 = add i32 %27, 1
  store i32 %addtmpi13, i32* %i
  br label %forcond
}