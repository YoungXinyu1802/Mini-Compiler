; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"ff\00"
@1 = private unnamed_addr constant [5 x i8] c"%s%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal void @ff(i32*) {
entry:
  %a = alloca i32*
  store i32* %0, i32** %a
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i8 10)
  ret void
}

define i32 @main() {
entry:
  %a = alloca [5 x i32]
  %0 = load [5 x i32], [5 x i32]* %a
  %1 = getelementptr [5 x i32], [5 x i32]* %a, i32 0, i32 0
  store i32 1, i32* %1
  %2 = getelementptr [5 x i32], [5 x i32]* %a, i32 0, i32 1
  store i32 2, i32* %2
  %3 = getelementptr [5 x i32], [5 x i32]* %a, i32 0, i32 2
  store i32 3, i32* %3
  %4 = getelementptr [5 x i32], [5 x i32]* %a, i32 0, i32 3
  store i32 4, i32* %4
  %5 = getelementptr [5 x i32], [5 x i32]* %a, i32 0, i32 4
  store i32 5, i32* %5
  %call = call void @ff([5 x i32]* %a)
}