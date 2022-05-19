; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [5 x i8] c"%s%c\00"
@1 = private unnamed_addr constant [5 x i8] c"%d%c\00"
@2 = private unnamed_addr constant [5 x i8] c"%s%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entry:
  %i = alloca i32
  %a = alloca [10 x i32]
  %0 = load [10 x i32], [10 x i32]* %a
  %1 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 0
  store i32 1, i32* %1
  %2 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 1
  store i32 2, i32* %2
  %3 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 2
  store i32 3, i32* %3
  %4 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 3
  store i32 4, i32* %4
  %5 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 4
  store i32 5, i32* %5
  %6 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 5
  store i32 6, i32* %6
  %7 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 6
  store i32 7, i32* %7
  %8 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 7
  store i32 8, i32* %8
  %9 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 8
  store i32 9, i32* %9
  %10 = getelementptr [10 x i32], [10 x i32]* %a, i32 0, i32 9
  store i32 10, i32* %10
  %11 = load [10 x i32], [10 x i32]* %a
  %12 = load [10 x i32], [10 x i32]* %a
  %13 = getelementptr [10 x i32], [10 x i32]* %a, i32 2
  %14 = load [10 x i32], [10 x i32]* %13
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), [10 x i32] %14, i8 10)
  store i32 2, i32* %i
  %15 = load i32, i32* %i
  %printf1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i32 %15, i8 10)
  %16 = load [10 x i32], [10 x i32]* %a
  %17 = load [10 x i32], [10 x i32]* %a
  %18 = getelementptr [10 x i32], [10 x i32]* %a, i32 2
  %19 = load [10 x i32], [10 x i32]* %18
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), [10 x i32] %19, i8 10)
  ret i32 0
}