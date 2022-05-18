; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [6 x i8] c"hello\00"
@1 = private unnamed_addr constant [5 x i8] c"%s%c\00"
@2 = private unnamed_addr constant [3 x i8] c"%c\00"
@3 = private unnamed_addr constant [5 x i8] c"%d%c\00"
@4 = private unnamed_addr constant [5 x i8] c"%d%c\00"
@5 = private unnamed_addr constant [5 x i8] c"%d%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entry:
  %c = alloca i8
  %str = alloca [10 x i8]
  %array = alloca [5 x i32]
  %i = alloca i32
  %b = alloca i32
  %a = alloca i32
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @0, i32 0, i32 0), i8 10)
  store i32 3, i32* %a
  %0 = load [5 x i32], [5 x i32]* %array
  %1 = getelementptr [5 x i32], [5 x i32]* %array, i32 0, i32 2
  store i32 10, i32* %1
  store i8 97, i8* %c
  %2 = load i8, i8* %c
  %printf1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i8 %2)
  %3 = load [10 x i8], [10 x i8]* %str
  %4 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 0
  store i8 100, i8* %4
  %5 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 1
  store i8 108, i8* %5
  %6 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 2
  store i8 114, i8* %6
  %7 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 3
  store i8 111, i8* %7
  %8 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 4
  store i8 119, i8* %8
  %9 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 5
  store i8 111, i8* %9
  %10 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 6
  store i8 108, i8* %10
  %11 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 7
  store i8 108, i8* %11
  %12 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 8
  store i8 101, i8* %12
  %13 = getelementptr [10 x i8], [10 x i8]* %str, i32 0, i32 9
  store i8 104, i8* %13
  %14 = load i32, i32* %a
  %cmptmpi = icmp eq i32 %14, 1
  %ifCond = icmp ne i1 %cmptmpi, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entry
  %15 = load i32, i32* %a
  %addtmpi = add i32 %15, 1
  store i32 %addtmpi, i32* %a
  br label %ifend

else:                                             ; preds = %entry
  %16 = load i32, i32* %a
  %cmptmpi2 = icmp eq i32 %16, 2
  %ifCond3 = icmp ne i1 %cmptmpi2, false
  br i1 %ifCond3, label %then4, label %else5

ifend:                                            ; preds = %ifend6, %then
  br label %cond

then4:                                            ; preds = %else
  %17 = load i32, i32* %a
  %addtmpi7 = add i32 %17, 2
  store i32 %addtmpi7, i32* %a
  br label %ifend6

else5:                                            ; preds = %else
  %18 = load i32, i32* %a
  %addtmpi8 = add i32 %18, 3
  store i32 %addtmpi8, i32* %b
  br label %ifend6

ifend6:                                           ; preds = %else5, %then4
  br label %ifend

cond:                                             ; preds = %loop, %ifend
  %19 = load i32, i32* %a
  %cmptmpi9 = icmp slt i32 %19, 10
  br i1 %cmptmpi9, label %loop, label %loopend

loop:                                             ; preds = %cond
  %20 = load i32, i32* %a
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @3, i32 0, i32 0), i32 %20, i8 32)
  %21 = load i32, i32* %b
  %addtmpi11 = add i32 %21, 3
  store i32 %addtmpi11, i32* %b
  %22 = load i32, i32* %a
  %addtmpi12 = add i32 %22, 1
  store i32 %addtmpi12, i32* %a
  br label %cond

loopend:                                          ; preds = %cond
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %forbody, %loopend
  %23 = load i32, i32* %i
  %cmptmpi13 = icmp slt i32 %23, 10
  br i1 %cmptmpi13, label %forbody, label %forend

forend:                                           ; preds = %forcond
  %24 = load i32, i32* %b
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @5, i32 0, i32 0), i32 %24, i8 10)
  ret i32 0

forbody:                                          ; preds = %forcond
  %25 = load i32, i32* %i
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @4, i32 0, i32 0), i32 %25, i8 10)
  %26 = load i32, i32* %i
  %addtmpi15 = add i32 %26, 1
  store i32 %addtmpi15, i32* %i
  br label %forcond
}