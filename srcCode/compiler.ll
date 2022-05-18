; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [5 x i8] c"%d%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal void @f(i32) {
entry:
  %a = alloca i32
  store i32 %0, i32* %a
  %1 = load i32, i32* %a
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32 %1, i8 10)
}

define i32 @Main() {
entry:
  %call = call void @f(i32 1)
  ret i32 0
}