; ModuleID = 'main'
source_filename = "main"

%Course = type { i32, [500 x i8], i32, i32, [5 x i8] }

@0 = private unnamed_addr constant [3 x i8] c"%c\00"
@1 = private unnamed_addr constant [3 x i8] c"%c\00"
@2 = private unnamed_addr constant [3 x i8] c"%d\00"
@3 = private unnamed_addr constant [3 x i8] c"%c\00"
@4 = private unnamed_addr constant [3 x i8] c"%c\00"
@5 = private unnamed_addr constant [3 x i8] c"%c\00"
@6 = private unnamed_addr constant [3 x i8] c"%c\00"
@7 = private unnamed_addr constant [6 x i8] c"GPA: \00"
@8 = private unnamed_addr constant [9 x i8] c"%s%.1f%c\00"
@9 = private unnamed_addr constant [18 x i8] c"Hours Attempted: \00"
@10 = private unnamed_addr constant [7 x i8] c"%s%d%c\00"
@11 = private unnamed_addr constant [18 x i8] c"Hours Completed: \00"
@12 = private unnamed_addr constant [7 x i8] c"%s%d%c\00"
@13 = private unnamed_addr constant [20 x i8] c"Credits Remaining: \00"
@14 = private unnamed_addr constant [7 x i8] c"%s%d%c\00"
@15 = private unnamed_addr constant [3 x i8] c"%c\00"
@16 = private unnamed_addr constant [30 x i8] c"Possible Courses to Take Next\00"
@17 = private unnamed_addr constant [5 x i8] c"%s%c\00"
@18 = private unnamed_addr constant [3 x i8] c"  \00"
@19 = private unnamed_addr constant [3 x i8] c"%s\00"
@20 = private unnamed_addr constant [3 x i8] c"%c\00"
@21 = private unnamed_addr constant [3 x i8] c"%c\00"
@22 = private unnamed_addr constant [3 x i8] c"  \00"
@23 = private unnamed_addr constant [3 x i8] c"%s\00"
@24 = private unnamed_addr constant [3 x i8] c"%c\00"
@25 = private unnamed_addr constant [3 x i8] c"%c\00"
@26 = private unnamed_addr constant [26 x i8] c"  None - Congratulations!\00"
@27 = private unnamed_addr constant [5 x i8] c"%s%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal i32 @HashFunc(i32, i32, i8*) {
entry:
  %rem = alloca i32
  %quotient = alloca i32
  %t = alloca i32
  %i = alloca i32
  %HashVal = alloca i32
  %key = alloca i8*
  %TableSize = alloca i32
  %size = alloca i32
  store i32 %0, i32* %size
  store i32 %1, i32* %TableSize
  store i8* %2, i8** %key
  store i32 0, i32* %HashVal
  store i32 0, i32* %i
  br label %cond

cond:                                             ; preds = %loop, %entry
  %3 = load i32, i32* %i
  %4 = load i32, i32* %size
  %cmptmpi = icmp ne i32 %3, %4
  br i1 %cmptmpi, label %loop, label %loopend

loop:                                             ; preds = %cond
  store i32 10, i32* %t
  %5 = load i32, i32* %HashVal
  %multmpi = mul i32 %5, 32
  %6 = load i32, i32* %t
  %addtmpi = add i32 %multmpi, %6
  store i32 %addtmpi, i32* %HashVal
  %7 = load i32, i32* %i
  %addtmpi1 = add i32 %7, 1
  store i32 %addtmpi1, i32* %i
  br label %cond

loopend:                                          ; preds = %cond
  %8 = load i32, i32* %HashVal
  %9 = load i32, i32* %TableSize
  %divtmpi = sdiv i32 %8, %9
  store i32 %divtmpi, i32* %quotient
  %10 = load i32, i32* %HashVal
  %11 = load i32, i32* %quotient
  %12 = load i32, i32* %TableSize
  %multmpi2 = mul i32 %11, %12
  %subtmpi = sub i32 %10, %multmpi2
  store i32 %subtmpi, i32* %rem
  %13 = load i32, i32* %rem
  ret i32 %13
}

define i32 @Main() {
entry:
  %flag = alloca i32
  %isOk = alloca i32
  %credited = alloca i32
  %tName = alloca [5 x i8]
  %myHashTable = alloca [1000 x i32]
  %nameSize = alloca i32
  %tableSize = alloca i32
  %tHash = alloca i32
  %courseNum = alloca i32
  %res1 = alloca double
  %totalRemain = alloca i32
  %length = alloca i32
  %credit = alloca i32
  %F = alloca i8
  %D = alloca i8
  %C = alloca i8
  %B = alloca i8
  %A = alloca i8
  %zero = alloca i8
  %test = alloca [2 x i8]
  %totalCourse = alloca i32
  %totalScore = alloca i32
  %totalHave = alloca i32
  %totalTried = alloca i32
  %totalGot = alloca i32
  %inEnd = alloca i32
  %t = alloca i32
  %count = alloca i32
  %index = alloca i32
  %type1 = alloca [100 x %Course]
  %z = alloca i32
  %k = alloca i32
  %j = alloca i32
  %i = alloca i32
  %con = alloca i32
  %temp = alloca i8
  store i32 1, i32* %con
  store i32 0, i32* %index
  store i32 0, i32* %count
  store i32 1, i32* %inEnd
  store i32 0, i32* %totalGot
  store i32 0, i32* %totalTried
  store i32 0, i32* %totalHave
  store i32 0, i32* %totalScore
  store i32 0, i32* %totalCourse
  %0 = getelementptr [2 x i8], [2 x i8]* %test, i32 0, i32 1
  %1 = load i8, i8* %0
  store i8 %1, i8* %zero
  store i8 65, i8* %A
  store i8 66, i8* %B
  store i8 67, i8* %C
  store i8 68, i8* %D
  store i8 70, i8* %F
  br label %cond

cond:                                             ; preds = %ifend, %entry
  %2 = load i32, i32* %inEnd
  %cmptmpi = icmp eq i32 %2, 1
  br i1 %cmptmpi, label %loop, label %loopend

loop:                                             ; preds = %cond
  store i32 1, i32* %con
  %3 = load i8, i8* %temp
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i8* %temp)
  %4 = load i8, i8* %temp
  %cmptmpi1 = icmp ne i8 %4, 10
  %ifCond = icmp ne i1 %cmptmpi1, false
  br i1 %ifCond, label %then, label %else

loopend:                                          ; preds = %cond
  %5 = load i32, i32* %totalHave
  %6 = load i32, i32* %totalGot
  %subtmpi = sub i32 %5, %6
  store i32 %subtmpi, i32* %totalRemain
  %7 = load i32, i32* %totalGot
  %cmptmpi77 = icmp ne i32 %7, 0
  %ifCond78 = icmp ne i1 %cmptmpi77, false
  br i1 %ifCond78, label %then79, label %else80

then:                                             ; preds = %loop
  %8 = load i32, i32* %totalCourse
  %addtmpi = add i32 %8, 1
  store i32 %addtmpi, i32* %totalCourse
  store i32 0, i32* %index
  br label %cond2

else:                                             ; preds = %loop
  store i32 0, i32* %inEnd
  br label %ifend

ifend:                                            ; preds = %else, %ifend32
  br label %cond

cond2:                                            ; preds = %ifend10, %then
  %9 = load i32, i32* %con
  %cmptmpi5 = icmp eq i32 %9, 1
  br i1 %cmptmpi5, label %loop3, label %loopend4

loop3:                                            ; preds = %cond2
  %10 = load i8, i8* %temp
  %cmptmpi6 = icmp eq i8 %10, 124
  %ifCond7 = icmp ne i1 %cmptmpi6, false
  br i1 %ifCond7, label %then8, label %else9

loopend4:                                         ; preds = %cond2
  %11 = load i32, i32* %credit
  %scanf13 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32* %credit)
  %12 = load i32, i32* %totalHave
  %13 = load i32, i32* %credit
  %addtmpi14 = add i32 %12, %13
  store i32 %addtmpi14, i32* %totalHave
  %14 = load i8, i8* %temp
  %scanf15 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @3, i32 0, i32 0), i8* %temp)
  store i32 1, i32* %con
  store i32 0, i32* %index
  store i32 0, i32* %length
  br label %cond16

then8:                                            ; preds = %loop3
  %15 = load i32, i32* %index
  %16 = load i32, i32* %count
  %17 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %16
  %18 = getelementptr %Course, %Course* %17, i32 0, i32 2
  store i32 %15, i32* %18
  store i32 0, i32* %index
  store i32 0, i32* %con
  br label %ifend10

else9:                                            ; preds = %loop3
  %19 = load i8, i8* %temp
  %20 = load i32, i32* %count
  %21 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %20
  %22 = getelementptr %Course, %Course* %21, i32 0, i32 4
  %23 = load i32, i32* %index
  %24 = getelementptr [5 x i8], [5 x i8]* %22, i32 0, i32 %23
  store i8 %19, i8* %24
  %25 = load i32, i32* %index
  %addtmpi11 = add i32 %25, 1
  store i32 %addtmpi11, i32* %index
  %26 = load i8, i8* %temp
  %scanf12 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8* %temp)
  br label %ifend10

ifend10:                                          ; preds = %else9, %then8
  br label %cond2

cond16:                                           ; preds = %ifend25, %loopend4
  %27 = load i32, i32* %con
  %cmptmpi19 = icmp eq i32 %27, 1
  br i1 %cmptmpi19, label %loop17, label %loopend18

loop17:                                           ; preds = %cond16
  %28 = load i8, i8* %temp
  %scanf20 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @4, i32 0, i32 0), i8* %temp)
  %29 = load i8, i8* %temp
  %cmptmpi21 = icmp eq i8 %29, 124
  %ifCond22 = icmp ne i1 %cmptmpi21, false
  br i1 %ifCond22, label %then23, label %else24

loopend18:                                        ; preds = %cond16
  %30 = load i8, i8* %temp
  %scanf27 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @5, i32 0, i32 0), i8* %temp)
  %31 = load i8, i8* %temp
  %cmptmpi28 = icmp eq i8 %31, 10
  %ifCond29 = icmp ne i1 %cmptmpi28, false
  br i1 %ifCond29, label %then30, label %else31

then23:                                           ; preds = %loop17
  %32 = load i32, i32* %index
  %33 = load i32, i32* %count
  %34 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %33
  %35 = getelementptr %Course, %Course* %34, i32 0, i32 0
  store i32 %32, i32* %35
  store i32 0, i32* %con
  br label %ifend25

else24:                                           ; preds = %loop17
  %36 = load i8, i8* %temp
  %37 = load i32, i32* %count
  %38 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %37
  %39 = getelementptr %Course, %Course* %38, i32 0, i32 1
  %40 = load i32, i32* %index
  %41 = getelementptr [500 x i8], [500 x i8]* %39, i32 0, i32 %40
  store i8 %36, i8* %41
  %42 = load i32, i32* %index
  %addtmpi26 = add i32 %42, 1
  store i32 %addtmpi26, i32* %index
  br label %ifend25

ifend25:                                          ; preds = %else24, %then23
  br label %cond16

then30:                                           ; preds = %loopend18
  %43 = load i32, i32* %count
  %44 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %43
  %45 = getelementptr %Course, %Course* %44, i32 0, i32 3
  store i32 -1, i32* %45
  %46 = load i32, i32* %count
  %addtmpi33 = add i32 %46, 1
  store i32 %addtmpi33, i32* %count
  br label %ifend32

else31:                                           ; preds = %loopend18
  %47 = load i8, i8* %temp
  %48 = load i8, i8* %A
  %cmptmpi34 = icmp eq i8 %47, %48
  %ifCond35 = icmp ne i1 %cmptmpi34, false
  br i1 %ifCond35, label %then36, label %else37

ifend32:                                          ; preds = %ifend38, %then30
  br label %ifend

then36:                                           ; preds = %else31
  store i32 4, i32* %t
  %49 = load i32, i32* %totalScore
  %50 = load i32, i32* %credit
  %multmpi = mul i32 4, %50
  %addtmpi39 = add i32 %49, %multmpi
  store i32 %addtmpi39, i32* %totalScore
  %51 = load i32, i32* %totalTried
  %52 = load i32, i32* %credit
  %addtmpi40 = add i32 %51, %52
  store i32 %addtmpi40, i32* %totalTried
  %53 = load i32, i32* %totalGot
  %54 = load i32, i32* %credit
  %addtmpi41 = add i32 %53, %54
  store i32 %addtmpi41, i32* %totalGot
  %55 = load i32, i32* %count
  %56 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %55
  %57 = getelementptr %Course, %Course* %56, i32 0, i32 3
  store i32 1, i32* %57
  br label %ifend38

else37:                                           ; preds = %else31
  %58 = load i8, i8* %temp
  %59 = load i8, i8* %B
  %cmptmpi42 = icmp eq i8 %58, %59
  %ifCond43 = icmp ne i1 %cmptmpi42, false
  br i1 %ifCond43, label %then44, label %else45

ifend38:                                          ; preds = %ifend46, %then36
  %60 = load i8, i8* %temp
  %scanf75 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @6, i32 0, i32 0), i8* %temp)
  %61 = load i32, i32* %count
  %addtmpi76 = add i32 %61, 1
  store i32 %addtmpi76, i32* %count
  br label %ifend32

then44:                                           ; preds = %else37
  store i32 3, i32* %t
  %62 = load i32, i32* %totalScore
  %63 = load i32, i32* %credit
  %multmpi47 = mul i32 3, %63
  %addtmpi48 = add i32 %62, %multmpi47
  store i32 %addtmpi48, i32* %totalScore
  %64 = load i32, i32* %totalTried
  %65 = load i32, i32* %credit
  %addtmpi49 = add i32 %64, %65
  store i32 %addtmpi49, i32* %totalTried
  %66 = load i32, i32* %totalGot
  %67 = load i32, i32* %credit
  %addtmpi50 = add i32 %66, %67
  store i32 %addtmpi50, i32* %totalGot
  %68 = load i32, i32* %count
  %69 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %68
  %70 = getelementptr %Course, %Course* %69, i32 0, i32 3
  store i32 1, i32* %70
  br label %ifend46

else45:                                           ; preds = %else37
  %71 = load i8, i8* %temp
  %72 = load i8, i8* %C
  %cmptmpi51 = icmp eq i8 %71, %72
  %ifCond52 = icmp ne i1 %cmptmpi51, false
  br i1 %ifCond52, label %then53, label %else54

ifend46:                                          ; preds = %ifend55, %then44
  br label %ifend38

then53:                                           ; preds = %else45
  store i32 2, i32* %t
  %73 = load i32, i32* %totalScore
  %74 = load i32, i32* %credit
  %multmpi56 = mul i32 2, %74
  %addtmpi57 = add i32 %73, %multmpi56
  store i32 %addtmpi57, i32* %totalScore
  %75 = load i32, i32* %totalTried
  %76 = load i32, i32* %credit
  %addtmpi58 = add i32 %75, %76
  store i32 %addtmpi58, i32* %totalTried
  %77 = load i32, i32* %totalGot
  %78 = load i32, i32* %credit
  %addtmpi59 = add i32 %77, %78
  store i32 %addtmpi59, i32* %totalGot
  %79 = load i32, i32* %count
  %80 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %79
  %81 = getelementptr %Course, %Course* %80, i32 0, i32 3
  store i32 1, i32* %81
  br label %ifend55

else54:                                           ; preds = %else45
  %82 = load i8, i8* %temp
  %83 = load i8, i8* %D
  %cmptmpi60 = icmp eq i8 %82, %83
  %ifCond61 = icmp ne i1 %cmptmpi60, false
  br i1 %ifCond61, label %then62, label %else63

ifend55:                                          ; preds = %ifend64, %then53
  br label %ifend46

then62:                                           ; preds = %else54
  store i32 1, i32* %t
  %84 = load i32, i32* %totalScore
  %85 = load i32, i32* %credit
  %multmpi65 = mul i32 1, %85
  %addtmpi66 = add i32 %84, %multmpi65
  store i32 %addtmpi66, i32* %totalScore
  %86 = load i32, i32* %totalTried
  %87 = load i32, i32* %credit
  %addtmpi67 = add i32 %86, %87
  store i32 %addtmpi67, i32* %totalTried
  %88 = load i32, i32* %totalGot
  %89 = load i32, i32* %credit
  %addtmpi68 = add i32 %88, %89
  store i32 %addtmpi68, i32* %totalGot
  %90 = load i32, i32* %count
  %91 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %90
  %92 = getelementptr %Course, %Course* %91, i32 0, i32 3
  store i32 1, i32* %92
  br label %ifend64

else63:                                           ; preds = %else54
  %93 = load i8, i8* %temp
  %94 = load i8, i8* %F
  %cmptmpi69 = icmp eq i8 %93, %94
  %ifCond70 = icmp ne i1 %cmptmpi69, false
  br i1 %ifCond70, label %then71, label %else72

ifend64:                                          ; preds = %ifend73, %then62
  br label %ifend55

then71:                                           ; preds = %else63
  store i32 0, i32* %t
  %95 = load i32, i32* %totalTried
  %96 = load i32, i32* %credit
  %addtmpi74 = add i32 %95, %96
  store i32 %addtmpi74, i32* %totalTried
  %97 = load i32, i32* %count
  %98 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %97
  %99 = getelementptr %Course, %Course* %98, i32 0, i32 3
  store i32 -1, i32* %99
  br label %ifend73

else72:                                           ; preds = %else63
  br label %ifend73

ifend73:                                          ; preds = %else72, %then71
  br label %ifend64

then79:                                           ; preds = %loopend
  %100 = load i32, i32* %totalScore
  %101 = sitofp i32 %100 to double
  %multmpf = fmul double 1.000000e+00, %101
  %102 = load i32, i32* %totalTried
  %103 = sitofp i32 %102 to double
  %divtmpf = fdiv double %multmpf, %103
  store double %divtmpf, double* %res1
  br label %ifend81

else80:                                           ; preds = %loopend
  store double 0.000000e+00, double* %res1
  br label %ifend81

ifend81:                                          ; preds = %else80, %then79
  %104 = load double, double* %res1
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @7, i32 0, i32 0), double %104, i8 10)
  %105 = load i32, i32* %totalTried
  %printf82 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @10, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @9, i32 0, i32 0), i32 %105, i8 10)
  %106 = load i32, i32* %totalGot
  %printf83 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @12, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @11, i32 0, i32 0), i32 %106, i8 10)
  %107 = load i32, i32* %totalRemain
  %printf84 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @14, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @13, i32 0, i32 0), i32 %107, i8 10)
  %printf85 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @15, i32 0, i32 0), i8 10)
  %printf86 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @17, i32 0, i32 0), i8* getelementptr inbounds ([30 x i8], [30 x i8]* @16, i32 0, i32 0), i8 10)
  store i32 0, i32* %courseNum
  store i32 0, i32* %tHash
  store i32 1000, i32* %tableSize
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %ifend97, %ifend81
  %108 = load i32, i32* %i
  %109 = load i32, i32* %totalCourse
  %cmptmpi87 = icmp slt i32 %108, %109
  br i1 %cmptmpi87, label %forbody, label %forend

forend:                                           ; preds = %forcond
  store i32 0, i32* %isOk
  store i32 0, i32* %i
  br label %forcond109

forbody:                                          ; preds = %forcond
  store i32 0, i32* %j
  br label %forcond88

forcond88:                                        ; preds = %forbody90, %forbody
  %110 = load i32, i32* %j
  %cmptmpi91 = icmp slt i32 %110, 5
  br i1 %cmptmpi91, label %forbody90, label %forend89

forend89:                                         ; preds = %forcond88
  %111 = load i32, i32* %i
  %112 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %111
  %113 = getelementptr %Course, %Course* %112, i32 0, i32 2
  %114 = load i32, i32* %113
  store i32 %114, i32* %nameSize
  %115 = load i32, i32* %nameSize
  %116 = load i32, i32* %tableSize
  %call = call i32 @HashFunc(i32 %115, i32 %116, [5 x i8]* %tName)
  store i32 %call, i32* %tHash
  %117 = load i32, i32* %i
  %118 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %117
  %119 = getelementptr %Course, %Course* %118, i32 0, i32 3
  %120 = load i32, i32* %119
  store i32 %120, i32* %credited
  %121 = load i32, i32* %tHash
  %122 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %121
  %123 = load i32, i32* %122
  %cmptmpi93 = icmp eq i32 %123, 0
  %ifCond94 = icmp ne i1 %cmptmpi93, false
  br i1 %ifCond94, label %then95, label %else96

forbody90:                                        ; preds = %forcond88
  %124 = load i32, i32* %i
  %125 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %124
  %126 = getelementptr %Course, %Course* %125, i32 0, i32 4
  %127 = load i32, i32* %j
  %128 = getelementptr [5 x i8], [5 x i8]* %126, i32 0, i32 %127
  %129 = load i8, i8* %128
  %130 = load i32, i32* %j
  %131 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %130
  store i8 %129, i8* %131
  %132 = load i32, i32* %j
  %addtmpi92 = add i32 %132, 1
  store i32 %addtmpi92, i32* %j
  br label %forcond88

then95:                                           ; preds = %forend89
  %133 = load i32, i32* %credited
  %cmptmpi98 = icmp eq i32 %133, -1
  %ifCond99 = icmp ne i1 %cmptmpi98, false
  br i1 %ifCond99, label %then100, label %else101

else96:                                           ; preds = %forend89
  %134 = load i32, i32* %tHash
  %135 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %134
  %136 = load i32, i32* %135
  %cmptmpi103 = icmp ne i32 %136, 0
  %ifCond104 = icmp ne i1 %cmptmpi103, false
  br i1 %ifCond104, label %then105, label %else106

ifend97:                                          ; preds = %ifend107, %ifend102
  %137 = load i32, i32* %i
  %addtmpi108 = add i32 %137, 1
  store i32 %addtmpi108, i32* %i
  br label %forcond

then100:                                          ; preds = %then95
  %138 = load i32, i32* %tHash
  %139 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %138
  store i32 1, i32* %139
  br label %ifend102

else101:                                          ; preds = %then95
  %140 = load i32, i32* %tHash
  %141 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %140
  store i32 2, i32* %141
  br label %ifend102

ifend102:                                         ; preds = %else101, %then100
  br label %ifend97

then105:                                          ; preds = %else96
  %142 = load i32, i32* %tHash
  %143 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %142
  store i32 3, i32* %143
  br label %ifend107

else106:                                          ; preds = %else96
  br label %ifend107

ifend107:                                         ; preds = %else106, %then105
  br label %ifend97

forcond109:                                       ; preds = %ifend117, %forend
  %144 = load i32, i32* %i
  %145 = load i32, i32* %totalCourse
  %cmptmpi112 = icmp slt i32 %144, %145
  br i1 %cmptmpi112, label %forbody111, label %forend110

forend110:                                        ; preds = %forcond109
  %146 = load i32, i32* %courseNum
  %cmptmpi297 = icmp eq i32 %146, 0
  %ifCond298 = icmp ne i1 %cmptmpi297, false
  br i1 %ifCond298, label %then299, label %else300

forbody111:                                       ; preds = %forcond109
  %147 = load i32, i32* %i
  %148 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %147
  %149 = getelementptr %Course, %Course* %148, i32 0, i32 3
  %150 = load i32, i32* %149
  %cmptmpi113 = icmp eq i32 %150, -1
  %ifCond114 = icmp ne i1 %cmptmpi113, false
  br i1 %ifCond114, label %then115, label %else116

then115:                                          ; preds = %forbody111
  %151 = load i32, i32* %i
  %152 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %151
  %153 = getelementptr %Course, %Course* %152, i32 0, i32 0
  %154 = load i32, i32* %153
  %cmptmpi118 = icmp eq i32 %154, 0
  %ifCond119 = icmp ne i1 %cmptmpi118, false
  br i1 %ifCond119, label %then120, label %else121

else116:                                          ; preds = %forbody111
  br label %ifend117

ifend117:                                         ; preds = %else116, %ifend122
  %155 = load i32, i32* %i
  %addtmpi296 = add i32 %155, 1
  store i32 %addtmpi296, i32* %i
  br label %forcond109

then120:                                          ; preds = %then115
  store i32 1, i32* %courseNum
  %printf123 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @19, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @18, i32 0, i32 0))
  store i32 0, i32* %j
  br label %forcond124

else121:                                          ; preds = %then115
  store i32 1, i32* %isOk
  store i32 0, i32* %index
  store i32 0, i32* %j
  br label %forcond131

ifend122:                                         ; preds = %ifend287, %forend125
  br label %ifend117

forcond124:                                       ; preds = %forbody126, %then120
  %156 = load i32, i32* %j
  %157 = load i32, i32* %nameSize
  %cmptmpi127 = icmp slt i32 %156, %157
  br i1 %cmptmpi127, label %forbody126, label %forend125

forend125:                                        ; preds = %forcond124
  %printf130 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @21, i32 0, i32 0), i8 10)
  br label %ifend122

forbody126:                                       ; preds = %forcond124
  %158 = load i32, i32* %i
  %159 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %158
  %160 = getelementptr %Course, %Course* %159, i32 0, i32 4
  %161 = load i32, i32* %j
  %162 = getelementptr [5 x i8], [5 x i8]* %160, i32 0, i32 %161
  %163 = load i8, i8* %162
  %printf128 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @20, i32 0, i32 0), i8 %163)
  %164 = load i32, i32* %j
  %addtmpi129 = add i32 %164, 1
  store i32 %addtmpi129, i32* %j
  br label %forcond124

forcond131:                                       ; preds = %ifend140, %else121
  %165 = load i32, i32* %j
  %166 = load i32, i32* %i
  %167 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %166
  %168 = getelementptr %Course, %Course* %167, i32 0, i32 0
  %169 = load i32, i32* %168
  %cmptmpi134 = icmp slt i32 %165, %169
  br i1 %cmptmpi134, label %forbody133, label %forend132

forend132:                                        ; preds = %forcond131
  %170 = load i8, i8* %temp
  %cmptmpi215 = icmp ne i8 %170, 59
  %ifCond216 = icmp ne i1 %cmptmpi215, false
  br i1 %ifCond216, label %then217, label %else218

forbody133:                                       ; preds = %forcond131
  %171 = load i32, i32* %i
  %172 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %171
  %173 = getelementptr %Course, %Course* %172, i32 0, i32 1
  %174 = load i32, i32* %j
  %175 = getelementptr [500 x i8], [500 x i8]* %173, i32 0, i32 %174
  %176 = load i8, i8* %175
  store i8 %176, i8* %temp
  %177 = load i8, i8* %temp
  %cmptmpi135 = icmp eq i8 %177, 44
  %178 = load i8, i8* %temp
  %cmptmpi136 = icmp eq i8 %178, 59
  %ortmp = or i1 %cmptmpi135, %cmptmpi136
  %ifCond137 = icmp ne i1 %ortmp, false
  br i1 %ifCond137, label %then138, label %else139

then138:                                          ; preds = %forbody133
  %179 = load i32, i32* %index
  store i32 %179, i32* %z
  br label %forcond141

else139:                                          ; preds = %forbody133
  %180 = load i8, i8* %temp
  %181 = load i32, i32* %index
  %182 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %181
  store i8 %180, i8* %182
  %183 = load i32, i32* %index
  %addtmpi213 = add i32 %183, 1
  store i32 %addtmpi213, i32* %index
  br label %ifend140

ifend140:                                         ; preds = %else139, %ifend207
  %184 = load i32, i32* %j
  %addtmpi214 = add i32 %184, 1
  store i32 %addtmpi214, i32* %j
  br label %forcond131

forcond141:                                       ; preds = %forbody143, %then138
  %185 = load i32, i32* %z
  %cmptmpi144 = icmp slt i32 %185, 5
  br i1 %cmptmpi144, label %forbody143, label %forend142

forend142:                                        ; preds = %forcond141
  %186 = load i32, i32* %index
  %187 = load i32, i32* %tableSize
  %call146 = call i32 @HashFunc(i32 %186, i32 %187, [5 x i8]* %tName)
  store i32 %call146, i32* %tHash
  store i32 0, i32* %index
  %188 = load i32, i32* %tHash
  %189 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %188
  %190 = load i32, i32* %189
  %cmptmpi147 = icmp eq i32 %190, 0
  %ifCond148 = icmp ne i1 %cmptmpi147, false
  br i1 %ifCond148, label %then149, label %else150

forbody143:                                       ; preds = %forcond141
  %191 = load i8, i8* %zero
  %192 = load i32, i32* %z
  %193 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %192
  store i8 %191, i8* %193
  %194 = load i32, i32* %z
  %addtmpi145 = add i32 %194, 1
  store i32 %addtmpi145, i32* %z
  br label %forcond141

then149:                                          ; preds = %forend142
  %195 = load i32, i32* %isOk
  %cmptmpi152 = icmp eq i32 %195, 1
  %ifCond153 = icmp ne i1 %cmptmpi152, false
  br i1 %ifCond153, label %then154, label %else155

else150:                                          ; preds = %forend142
  %196 = load i32, i32* %tHash
  %197 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %196
  %198 = load i32, i32* %197
  %cmptmpi157 = icmp eq i32 %198, 1
  %ifCond158 = icmp ne i1 %cmptmpi157, false
  br i1 %ifCond158, label %then159, label %else160

ifend151:                                         ; preds = %ifend161, %ifend156
  %199 = load i8, i8* %temp
  %cmptmpi203 = icmp eq i8 %199, 59
  %ifCond204 = icmp ne i1 %cmptmpi203, false
  br i1 %ifCond204, label %then205, label %else206

then154:                                          ; preds = %then149
  store i32 0, i32* %isOk
  br label %ifend156

else155:                                          ; preds = %then149
  br label %ifend156

ifend156:                                         ; preds = %else155, %then154
  br label %ifend151

then159:                                          ; preds = %else150
  %200 = load i32, i32* %isOk
  %cmptmpi162 = icmp eq i32 %200, 1
  %ifCond163 = icmp ne i1 %cmptmpi162, false
  br i1 %ifCond163, label %then164, label %else165

else160:                                          ; preds = %else150
  %201 = load i32, i32* %tHash
  %202 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %201
  %203 = load i32, i32* %202
  %cmptmpi167 = icmp eq i32 %203, 2
  %ifCond168 = icmp ne i1 %cmptmpi167, false
  br i1 %ifCond168, label %then169, label %else170

ifend161:                                         ; preds = %ifend171, %ifend166
  br label %ifend151

then164:                                          ; preds = %then159
  store i32 0, i32* %isOk
  br label %ifend166

else165:                                          ; preds = %then159
  br label %ifend166

ifend166:                                         ; preds = %else165, %then164
  br label %ifend161

then169:                                          ; preds = %else160
  %204 = load i32, i32* %isOk
  %cmptmpi172 = icmp eq i32 %204, 1
  %ifCond173 = icmp ne i1 %cmptmpi172, false
  br i1 %ifCond173, label %then174, label %else175

else170:                                          ; preds = %else160
  store i32 0, i32* %k
  br label %forcond177

ifend171:                                         ; preds = %forend178, %ifend176
  br label %ifend161

then174:                                          ; preds = %then169
  store i32 1, i32* %isOk
  br label %ifend176

else175:                                          ; preds = %then169
  br label %ifend176

ifend176:                                         ; preds = %else175, %then174
  br label %ifend171

forcond177:                                       ; preds = %ifend195, %else170
  %205 = load i32, i32* %k
  %206 = load i32, i32* %totalCourse
  %cmptmpi180 = icmp slt i32 %205, %206
  br i1 %cmptmpi180, label %forbody179, label %forend178

forend178:                                        ; preds = %forcond177
  br label %ifend171

forbody179:                                       ; preds = %forcond177
  store i32 1, i32* %flag
  store i32 0, i32* %z
  br label %forcond181

forcond181:                                       ; preds = %ifend189, %forbody179
  %207 = load i32, i32* %z
  %cmptmpi184 = icmp slt i32 %207, 5
  br i1 %cmptmpi184, label %forbody183, label %forend182

forend182:                                        ; preds = %forcond181
  %208 = load i32, i32* %flag
  %cmptmpi191 = icmp eq i32 %208, 1
  %ifCond192 = icmp ne i1 %cmptmpi191, false
  br i1 %ifCond192, label %then193, label %else194

forbody183:                                       ; preds = %forcond181
  %209 = load i32, i32* %k
  %210 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %209
  %211 = getelementptr %Course, %Course* %210, i32 0, i32 4
  %212 = load i32, i32* %z
  %213 = getelementptr [5 x i8], [5 x i8]* %211, i32 0, i32 %212
  %214 = load i8, i8* %213
  %215 = load i32, i32* %z
  %216 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %215
  %217 = load i8, i8* %216
  %cmptmpi185 = icmp ne i8 %214, %217
  %ifCond186 = icmp ne i1 %cmptmpi185, false
  br i1 %ifCond186, label %then187, label %else188

then187:                                          ; preds = %forbody183
  store i32 -1, i32* %flag
  store i32 5, i32* %z
  br label %ifend189

else188:                                          ; preds = %forbody183
  br label %ifend189

ifend189:                                         ; preds = %else188, %then187
  %218 = load i32, i32* %z
  %addtmpi190 = add i32 %218, 1
  store i32 %addtmpi190, i32* %z
  br label %forcond181

then193:                                          ; preds = %forend182
  %219 = load i32, i32* %k
  %220 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %219
  %221 = getelementptr %Course, %Course* %220, i32 0, i32 3
  %222 = load i32, i32* %221
  %cmptmpi196 = icmp eq i32 %222, 1
  %223 = load i32, i32* %isOk
  %cmptmpi197 = icmp eq i32 %223, 1
  %andtmp = and i1 %cmptmpi196, %cmptmpi197
  %ifCond198 = icmp ne i1 %andtmp, false
  br i1 %ifCond198, label %then199, label %else200

else194:                                          ; preds = %forend182
  br label %ifend195

ifend195:                                         ; preds = %else194, %ifend201
  %224 = load i32, i32* %k
  %addtmpi202 = add i32 %224, 1
  store i32 %addtmpi202, i32* %k
  br label %forcond177

then199:                                          ; preds = %then193
  store i32 1, i32* %isOk
  br label %ifend201

else200:                                          ; preds = %then193
  store i32 -1, i32* %isOk
  br label %ifend201

ifend201:                                         ; preds = %else200, %then199
  %225 = load i32, i32* %totalCourse
  store i32 %225, i32* %k
  br label %ifend195

then205:                                          ; preds = %ifend151
  %226 = load i32, i32* %isOk
  %cmptmpi208 = icmp eq i32 %226, 1
  %ifCond209 = icmp ne i1 %cmptmpi208, false
  br i1 %ifCond209, label %then210, label %else211

else206:                                          ; preds = %ifend151
  br label %ifend207

ifend207:                                         ; preds = %else206, %ifend212
  br label %ifend140

then210:                                          ; preds = %then205
  %227 = load i32, i32* %i
  %228 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %227
  %229 = getelementptr %Course, %Course* %228, i32 0, i32 0
  %230 = load i32, i32* %229
  store i32 %230, i32* %j
  br label %ifend212

else211:                                          ; preds = %then205
  store i32 1, i32* %isOk
  br label %ifend212

ifend212:                                         ; preds = %else211, %then210
  br label %ifend207

then217:                                          ; preds = %forend132
  %231 = load i32, i32* %index
  store i32 %231, i32* %nameSize
  %232 = load i32, i32* %index
  store i32 %232, i32* %z
  br label %forcond220

else218:                                          ; preds = %forend132
  br label %ifend219

ifend219:                                         ; preds = %else218, %ifend230
  %233 = load i32, i32* %isOk
  %cmptmpi283 = icmp eq i32 %233, 1
  %ifCond284 = icmp ne i1 %cmptmpi283, false
  br i1 %ifCond284, label %then285, label %else286

forcond220:                                       ; preds = %forbody222, %then217
  %234 = load i32, i32* %z
  %cmptmpi223 = icmp slt i32 %234, 5
  br i1 %cmptmpi223, label %forbody222, label %forend221

forend221:                                        ; preds = %forcond220
  %235 = load i32, i32* %nameSize
  %236 = load i32, i32* %tableSize
  %call225 = call i32 @HashFunc(i32 %235, i32 %236, [5 x i8]* %tName)
  store i32 %call225, i32* %tHash
  %237 = load i32, i32* %tHash
  %238 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %237
  %239 = load i32, i32* %238
  %cmptmpi226 = icmp eq i32 %239, 0
  %ifCond227 = icmp ne i1 %cmptmpi226, false
  br i1 %ifCond227, label %then228, label %else229

forbody222:                                       ; preds = %forcond220
  %240 = load i8, i8* %zero
  %241 = load i32, i32* %z
  %242 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %241
  store i8 %240, i8* %242
  %243 = load i32, i32* %z
  %addtmpi224 = add i32 %243, 1
  store i32 %addtmpi224, i32* %z
  br label %forcond220

then228:                                          ; preds = %forend221
  %244 = load i32, i32* %isOk
  %cmptmpi231 = icmp eq i32 %244, 1
  %ifCond232 = icmp ne i1 %cmptmpi231, false
  br i1 %ifCond232, label %then233, label %else234

else229:                                          ; preds = %forend221
  %245 = load i32, i32* %tHash
  %246 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %245
  %247 = load i32, i32* %246
  %cmptmpi236 = icmp eq i32 %247, 1
  %ifCond237 = icmp ne i1 %cmptmpi236, false
  br i1 %ifCond237, label %then238, label %else239

ifend230:                                         ; preds = %ifend240, %ifend235
  br label %ifend219

then233:                                          ; preds = %then228
  store i32 0, i32* %isOk
  br label %ifend235

else234:                                          ; preds = %then228
  br label %ifend235

ifend235:                                         ; preds = %else234, %then233
  br label %ifend230

then238:                                          ; preds = %else229
  %248 = load i32, i32* %isOk
  %cmptmpi241 = icmp eq i32 %248, 1
  %ifCond242 = icmp ne i1 %cmptmpi241, false
  br i1 %ifCond242, label %then243, label %else244

else239:                                          ; preds = %else229
  %249 = load i32, i32* %tHash
  %250 = getelementptr [1000 x i32], [1000 x i32]* %myHashTable, i32 0, i32 %249
  %251 = load i32, i32* %250
  %cmptmpi246 = icmp eq i32 %251, 2
  %ifCond247 = icmp ne i1 %cmptmpi246, false
  br i1 %ifCond247, label %then248, label %else249

ifend240:                                         ; preds = %ifend250, %ifend245
  br label %ifend230

then243:                                          ; preds = %then238
  store i32 0, i32* %isOk
  br label %ifend245

else244:                                          ; preds = %then238
  br label %ifend245

ifend245:                                         ; preds = %else244, %then243
  br label %ifend240

then248:                                          ; preds = %else239
  %252 = load i32, i32* %isOk
  %cmptmpi251 = icmp eq i32 %252, 1
  %ifCond252 = icmp ne i1 %cmptmpi251, false
  br i1 %ifCond252, label %then253, label %else254

else249:                                          ; preds = %else239
  store i32 0, i32* %k
  br label %forcond256

ifend250:                                         ; preds = %forend257, %ifend255
  br label %ifend240

then253:                                          ; preds = %then248
  store i32 1, i32* %isOk
  br label %ifend255

else254:                                          ; preds = %then248
  br label %ifend255

ifend255:                                         ; preds = %else254, %then253
  br label %ifend250

forcond256:                                       ; preds = %ifend274, %else249
  %253 = load i32, i32* %k
  %254 = load i32, i32* %totalCourse
  %cmptmpi259 = icmp slt i32 %253, %254
  br i1 %cmptmpi259, label %forbody258, label %forend257

forend257:                                        ; preds = %forcond256
  br label %ifend250

forbody258:                                       ; preds = %forcond256
  store i32 1, i32* %flag
  store i32 0, i32* %z
  br label %forcond260

forcond260:                                       ; preds = %ifend268, %forbody258
  %255 = load i32, i32* %z
  %cmptmpi263 = icmp slt i32 %255, 5
  br i1 %cmptmpi263, label %forbody262, label %forend261

forend261:                                        ; preds = %forcond260
  %256 = load i32, i32* %flag
  %cmptmpi270 = icmp eq i32 %256, 1
  %ifCond271 = icmp ne i1 %cmptmpi270, false
  br i1 %ifCond271, label %then272, label %else273

forbody262:                                       ; preds = %forcond260
  %257 = load i32, i32* %k
  %258 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %257
  %259 = getelementptr %Course, %Course* %258, i32 0, i32 4
  %260 = load i32, i32* %z
  %261 = getelementptr [5 x i8], [5 x i8]* %259, i32 0, i32 %260
  %262 = load i8, i8* %261
  %263 = load i32, i32* %z
  %264 = getelementptr [5 x i8], [5 x i8]* %tName, i32 0, i32 %263
  %265 = load i8, i8* %264
  %cmptmpi264 = icmp ne i8 %262, %265
  %ifCond265 = icmp ne i1 %cmptmpi264, false
  br i1 %ifCond265, label %then266, label %else267

then266:                                          ; preds = %forbody262
  store i32 -1, i32* %flag
  store i32 5, i32* %z
  br label %ifend268

else267:                                          ; preds = %forbody262
  br label %ifend268

ifend268:                                         ; preds = %else267, %then266
  %266 = load i32, i32* %z
  %addtmpi269 = add i32 %266, 1
  store i32 %addtmpi269, i32* %z
  br label %forcond260

then272:                                          ; preds = %forend261
  %267 = load i32, i32* %k
  %268 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %267
  %269 = getelementptr %Course, %Course* %268, i32 0, i32 3
  %270 = load i32, i32* %269
  %cmptmpi275 = icmp eq i32 %270, 1
  %271 = load i32, i32* %isOk
  %cmptmpi276 = icmp eq i32 %271, 1
  %andtmp277 = and i1 %cmptmpi275, %cmptmpi276
  %ifCond278 = icmp ne i1 %andtmp277, false
  br i1 %ifCond278, label %then279, label %else280

else273:                                          ; preds = %forend261
  br label %ifend274

ifend274:                                         ; preds = %else273, %ifend281
  %272 = load i32, i32* %k
  %addtmpi282 = add i32 %272, 1
  store i32 %addtmpi282, i32* %k
  br label %forcond256

then279:                                          ; preds = %then272
  store i32 1, i32* %isOk
  br label %ifend281

else280:                                          ; preds = %then272
  store i32 -1, i32* %isOk
  br label %ifend281

ifend281:                                         ; preds = %else280, %then279
  %273 = load i32, i32* %totalCourse
  store i32 %273, i32* %k
  br label %ifend274

then285:                                          ; preds = %ifend219
  store i32 1, i32* %courseNum
  %printf288 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @23, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @22, i32 0, i32 0))
  store i32 0, i32* %j
  br label %forcond289

else286:                                          ; preds = %ifend219
  br label %ifend287

ifend287:                                         ; preds = %else286, %forend290
  br label %ifend122

forcond289:                                       ; preds = %forbody291, %then285
  %274 = load i32, i32* %j
  %275 = load i32, i32* %nameSize
  %cmptmpi292 = icmp slt i32 %274, %275
  br i1 %cmptmpi292, label %forbody291, label %forend290

forend290:                                        ; preds = %forcond289
  %printf295 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @25, i32 0, i32 0), i8 10)
  br label %ifend287

forbody291:                                       ; preds = %forcond289
  %276 = load i32, i32* %i
  %277 = getelementptr [100 x %Course], [100 x %Course]* %type1, i32 0, i32 %276
  %278 = getelementptr %Course, %Course* %277, i32 0, i32 4
  %279 = load i32, i32* %j
  %280 = getelementptr [5 x i8], [5 x i8]* %278, i32 0, i32 %279
  %281 = load i8, i8* %280
  %printf293 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @24, i32 0, i32 0), i8 %281)
  %282 = load i32, i32* %j
  %addtmpi294 = add i32 %282, 1
  store i32 %addtmpi294, i32* %j
  br label %forcond289

then299:                                          ; preds = %forend110
  %printf302 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @27, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @26, i32 0, i32 0), i8 10)
  br label %ifend301

else300:                                          ; preds = %forend110
  br label %ifend301

ifend301:                                         ; preds = %else300, %then299
  ret i32 0
}
Wrote output.o
