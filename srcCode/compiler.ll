; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [5 x i8] c"%d%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal i32 @f(i32, i32) {
entry:
  %b = alloca i32
  %a = alloca i32
  store i32 %0, i32* %a
  store i32 %1, i32* %b
  %2 = load i32, i32* %a
  ret i32 %2
}

define i32 @Main() {
entry:
  %b = alloca i32
  %a = alloca i32
  %call = call i32 @f(i32 2, i32 1)
  ret i32 %call
  store i32 %call, i32* %a
  %0 = load i32, i32* %a
  store i32 %0, i32* %b
  %1 = load i32, i32* %b
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32 %1, i8 10)
  ret i32 0
}