; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [3 x i8] c"%d\00"
@2 = private unnamed_addr constant [5 x i8] c"%d%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal void @quicksort(i32, i32, i32*) {
entry:
  %newlow = alloca i32
  %newhigh = alloca i32
  %flag = alloca i32
  %temp = alloca i32
  %key = alloca i32
  %j = alloca i32
  %i = alloca i32
  %a = alloca i32*
  %low = alloca i32
  %high = alloca i32
  store i32 %0, i32* %high
  store i32 %1, i32* %low
  store i32* %2, i32** %a
  store i32 0, i32* %flag
  %3 = load i32, i32* %low
  store i32 %3, i32* %i
  %4 = load i32, i32* %high
  store i32 %4, i32* %j
  %5 = load i32, i32* %low
  %6 = load i32*, i32** %a
  %7 = getelementptr i32, i32* %6, i32 %5
  %8 = load i32, i32* %7
  store i32 %8, i32* %key
  %9 = load i32, i32* %low
  %10 = load i32, i32* %high
  %cmptmpi = icmp sge i32 %9, %10
  %ifCond = icmp ne i1 %cmptmpi, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entry
  store i32 1, i32* %flag
  br label %ifend

else:                                             ; preds = %entry
  br label %ifend

ifend:                                            ; preds = %else, %then
  %11 = load i32, i32* %flag
  %cmptmpi1 = icmp eq i32 %11, 0
  %ifCond2 = icmp ne i1 %cmptmpi1, false
  br i1 %ifCond2, label %then3, label %else4

then3:                                            ; preds = %ifend
  br label %cond

else4:                                            ; preds = %ifend
  br label %ifend5

ifend5:                                           ; preds = %else4, %loopend
  ret void

cond:                                             ; preds = %ifend28, %then3
  %12 = load i32, i32* %low
  %13 = load i32, i32* %high
  %cmptmpi6 = icmp slt i32 %12, %13
  br i1 %cmptmpi6, label %loop, label %loopend

loop:                                             ; preds = %cond
  br label %cond7

loopend:                                          ; preds = %cond
  %14 = load i32, i32* %low
  %subtmpi30 = sub i32 %14, 1
  store i32 %subtmpi30, i32* %newhigh
  %15 = load i32, i32* %low
  %addtmpi31 = add i32 %15, 1
  store i32 %addtmpi31, i32* %newlow
  %16 = load i32, i32* %newhigh
  %17 = load i32, i32* %i
  %18 = load i32*, i32** %a
  %call = call void @quicksort(i32 %16, i32 %17, i32* %18)
  %19 = load i32, i32* %j
  %20 = load i32, i32* %newlow
  %21 = load i32*, i32** %a
  %call32 = call void @quicksort(i32 %19, i32 %20, i32* %21)
  br label %ifend5

cond7:                                            ; preds = %loop8, %loop
  %22 = load i32, i32* %low
  %23 = load i32, i32* %high
  %cmptmpi10 = icmp slt i32 %22, %23
  %24 = load i32, i32* %key
  %25 = load i32, i32* %high
  %26 = load i32*, i32** %a
  %27 = getelementptr i32, i32* %26, i32 %25
  %28 = load i32, i32* %27
  %cmptmpi11 = icmp sle i32 %24, %28
  %andtmp = and i1 %cmptmpi10, %cmptmpi11
  br i1 %andtmp, label %loop8, label %loopend9

loop8:                                            ; preds = %cond7
  %29 = load i32, i32* %high
  %subtmpi = sub i32 %29, 1
  store i32 %subtmpi, i32* %high
  br label %cond7

loopend9:                                         ; preds = %cond7
  %30 = load i32, i32* %key
  %31 = load i32, i32* %high
  %32 = load i32*, i32** %a
  %33 = getelementptr i32, i32* %32, i32 %31
  %34 = load i32, i32* %33
  %cmptmpi12 = icmp sgt i32 %30, %34
  %ifCond13 = icmp ne i1 %cmptmpi12, false
  br i1 %ifCond13, label %then14, label %else15

then14:                                           ; preds = %loopend9
  %35 = load i32, i32* %low
  %36 = load i32*, i32** %a
  %37 = getelementptr i32, i32* %36, i32 %35
  %38 = load i32, i32* %37
  store i32 %38, i32* %temp
  %39 = load i32, i32* %high
  %40 = load i32*, i32** %a
  %41 = getelementptr i32, i32* %40, i32 %39
  %42 = load i32, i32* %41
  %43 = load i32, i32* %low
  %44 = load i32*, i32** %a
  %45 = load i32*, i32** %a
  %46 = getelementptr i32, i32* %45, i32 %43
  store i32 %42, i32* %46
  %47 = load i32, i32* %temp
  %48 = load i32, i32* %high
  %49 = load i32*, i32** %a
  %50 = load i32*, i32** %a
  %51 = getelementptr i32, i32* %50, i32 %48
  store i32 %47, i32* %51
  %52 = load i32, i32* %low
  %addtmpi = add i32 %52, 1
  store i32 %addtmpi, i32* %low
  br label %ifend16

else15:                                           ; preds = %loopend9
  br label %ifend16

ifend16:                                          ; preds = %else15, %then14
  br label %cond17

cond17:                                           ; preds = %loop18, %ifend16
  %53 = load i32, i32* %low
  %54 = load i32, i32* %high
  %cmptmpi20 = icmp slt i32 %53, %54
  %55 = load i32, i32* %key
  %56 = load i32, i32* %low
  %57 = load i32*, i32** %a
  %58 = getelementptr i32, i32* %57, i32 %56
  %59 = load i32, i32* %58
  %cmptmpi21 = icmp sge i32 %55, %59
  %andtmp22 = and i1 %cmptmpi20, %cmptmpi21
  br i1 %andtmp22, label %loop18, label %loopend19

loop18:                                           ; preds = %cond17
  %60 = load i32, i32* %low
  %addtmpi23 = add i32 %60, 1
  store i32 %addtmpi23, i32* %low
  br label %cond17

loopend19:                                        ; preds = %cond17
  %61 = load i32, i32* %key
  %62 = load i32, i32* %low
  %63 = load i32*, i32** %a
  %64 = getelementptr i32, i32* %63, i32 %62
  %65 = load i32, i32* %64
  %cmptmpi24 = icmp slt i32 %61, %65
  %ifCond25 = icmp ne i1 %cmptmpi24, false
  br i1 %ifCond25, label %then26, label %else27

then26:                                           ; preds = %loopend19
  %66 = load i32, i32* %low
  %67 = load i32*, i32** %a
  %68 = getelementptr i32, i32* %67, i32 %66
  %69 = load i32, i32* %68
  store i32 %69, i32* %temp
  %70 = load i32, i32* %high
  %71 = load i32*, i32** %a
  %72 = getelementptr i32, i32* %71, i32 %70
  %73 = load i32, i32* %72
  %74 = load i32, i32* %low
  %75 = load i32*, i32** %a
  %76 = load i32*, i32** %a
  %77 = getelementptr i32, i32* %76, i32 %74
  store i32 %73, i32* %77
  %78 = load i32, i32* %temp
  %79 = load i32, i32* %high
  %80 = load i32*, i32** %a
  %81 = load i32*, i32** %a
  %82 = getelementptr i32, i32* %81, i32 %79
  store i32 %78, i32* %82
  %83 = load i32, i32* %high
  %subtmpi29 = sub i32 %83, 1
  store i32 %subtmpi29, i32* %high
  br label %ifend28

else27:                                           ; preds = %loopend19
  br label %ifend28

ifend28:                                          ; preds = %else27, %then26
  br label %cond
}

define i32 @Main() {
entry:
  %temp = alloca i32
  %i = alloca i32
  %n = alloca i32
  %a = alloca [10000 x i32]
  %0 = load i32, i32* %n
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %n)
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %forbody, %entry
  %1 = load i32, i32* %i
  %2 = load i32, i32* %n
  %cmptmpi = icmp slt i32 %1, %2
  br i1 %cmptmpi, label %forbody, label %forend

forend:                                           ; preds = %forcond
  %3 = load i32, i32* %n
  %subtmpi = sub i32 %3, 1
  store i32 %subtmpi, i32* %temp
  %4 = load i32, i32* %temp
  %call = call void @quicksort(i32 %4, i32 0, [10000 x i32]* %a)
  store i32 0, i32* %i
  br label %forcond2

forbody:                                          ; preds = %forcond
  %5 = load i32, i32* %temp
  %scanf1 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %temp)
  %6 = load i32, i32* %temp
  %7 = load i32, i32* %i
  %8 = load [10000 x i32], [10000 x i32]* %a
  %9 = getelementptr [10000 x i32], [10000 x i32]* %a, i32 0, i32 %7
  store i32 %6, i32* %9
  %10 = load i32, i32* %i
  %addtmpi = add i32 %10, 1
  store i32 %addtmpi, i32* %i
  br label %forcond

forcond2:                                         ; preds = %forbody4, %forend
  %11 = load i32, i32* %i
  %12 = load i32, i32* %n
  %cmptmpi5 = icmp slt i32 %11, %12
  br i1 %cmptmpi5, label %forbody4, label %forend3

forend3:                                          ; preds = %forcond2
  ret i32 0

forbody4:                                         ; preds = %forcond2
  %13 = load i32, i32* %i
  %14 = getelementptr [10000 x i32], [10000 x i32]* %a, i32 0, i32 %13
  %15 = load i32, i32* %14
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), i32 %15, i8 10)
  %16 = load i32, i32* %i
  %addtmpi6 = add i32 %16, 1
  store i32 %addtmpi6, i32* %i
  br label %forcond2
}