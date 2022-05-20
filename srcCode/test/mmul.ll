; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [5 x i8] c"%d%d\00"
@1 = private unnamed_addr constant [3 x i8] c"%d\00"
@2 = private unnamed_addr constant [5 x i8] c"%d%d\00"
@3 = private unnamed_addr constant [3 x i8] c"%d\00"
@4 = private unnamed_addr constant [24 x i8] c"Incompatible Dimensions\00"
@5 = private unnamed_addr constant [5 x i8] c"%s%c\00"
@6 = private unnamed_addr constant [5 x i8] c"%10d\00"
@7 = private unnamed_addr constant [3 x i8] c"%c\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @Main() {
entry:
  %t = alloca i32
  %z = alloca i32
  %y = alloca i32
  %x = alloca i32
  %C = alloca [625 x i32]
  %n3 = alloca i32
  %B = alloca [625 x i32]
  %n2 = alloca i32
  %temp = alloca i32
  %k = alloca i32
  %j = alloca i32
  %i = alloca i32
  %A = alloca [625 x i32]
  %n1 = alloca i32
  %N2 = alloca i32
  %M2 = alloca i32
  %N1 = alloca i32
  %M1 = alloca i32
  %0 = load i32, i32* %M1
  %1 = load i32, i32* %N1
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32* %M1, i32* %N1)
  %2 = load i32, i32* %M1
  %3 = load i32, i32* %N1
  %multmpi = mul i32 %2, %3
  store i32 %multmpi, i32* %n1
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %forend2, %entry
  %4 = load i32, i32* %i
  %5 = load i32, i32* %M1
  %cmptmpi = icmp slt i32 %4, %5
  br i1 %cmptmpi, label %forbody, label %forend

forend:                                           ; preds = %forcond
  %6 = load i32, i32* %M2
  %7 = load i32, i32* %N2
  %scanf9 = call i32 (...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), i32* %M2, i32* %N2)
  %8 = load i32, i32* %M2
  %9 = load i32, i32* %N2
  %multmpi10 = mul i32 %8, %9
  store i32 %multmpi10, i32* %n2
  store i32 0, i32* %i
  br label %forcond11

forbody:                                          ; preds = %forcond
  store i32 0, i32* %j
  br label %forcond1

forcond1:                                         ; preds = %forbody3, %forbody
  %10 = load i32, i32* %j
  %11 = load i32, i32* %N1
  %cmptmpi4 = icmp slt i32 %10, %11
  br i1 %cmptmpi4, label %forbody3, label %forend2

forend2:                                          ; preds = %forcond1
  %12 = load i32, i32* %i
  %addtmpi8 = add i32 %12, 1
  store i32 %addtmpi8, i32* %i
  br label %forcond

forbody3:                                         ; preds = %forcond1
  %13 = load i32, i32* %i
  %14 = load i32, i32* %N1
  %multmpi5 = mul i32 %13, %14
  %15 = load i32, i32* %j
  %addtmpi = add i32 %multmpi5, %15
  store i32 %addtmpi, i32* %k
  %16 = load i32, i32* %temp
  %scanf6 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %temp)
  %17 = load i32, i32* %temp
  %18 = load i32, i32* %k
  %19 = load [625 x i32], [625 x i32]* %A
  %20 = getelementptr [625 x i32], [625 x i32]* %A, i32 0, i32 %18
  store i32 %17, i32* %20
  %21 = load i32, i32* %j
  %addtmpi7 = add i32 %21, 1
  store i32 %addtmpi7, i32* %j
  br label %forcond1

forcond11:                                        ; preds = %forend16, %forend
  %22 = load i32, i32* %i
  %23 = load i32, i32* %M2
  %cmptmpi14 = icmp slt i32 %22, %23
  br i1 %cmptmpi14, label %forbody13, label %forend12

forend12:                                         ; preds = %forcond11
  %24 = load i32, i32* %M1
  %25 = load i32, i32* %N2
  %multmpi24 = mul i32 %24, %25
  store i32 %multmpi24, i32* %n3
  %26 = load i32, i32* %N1
  %27 = load i32, i32* %M2
  %cmptmpi25 = icmp ne i32 %26, %27
  %ifCond = icmp ne i1 %cmptmpi25, false
  br i1 %ifCond, label %then, label %else

forbody13:                                        ; preds = %forcond11
  store i32 0, i32* %j
  br label %forcond15

forcond15:                                        ; preds = %forbody17, %forbody13
  %28 = load i32, i32* %j
  %29 = load i32, i32* %N2
  %cmptmpi18 = icmp slt i32 %28, %29
  br i1 %cmptmpi18, label %forbody17, label %forend16

forend16:                                         ; preds = %forcond15
  %30 = load i32, i32* %i
  %addtmpi23 = add i32 %30, 1
  store i32 %addtmpi23, i32* %i
  br label %forcond11

forbody17:                                        ; preds = %forcond15
  %31 = load i32, i32* %i
  %32 = load i32, i32* %N2
  %multmpi19 = mul i32 %31, %32
  %33 = load i32, i32* %j
  %addtmpi20 = add i32 %multmpi19, %33
  store i32 %addtmpi20, i32* %k
  %34 = load i32, i32* %temp
  %scanf21 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @3, i32 0, i32 0), i32* %temp)
  %35 = load i32, i32* %temp
  %36 = load i32, i32* %k
  %37 = load [625 x i32], [625 x i32]* %B
  %38 = getelementptr [625 x i32], [625 x i32]* %B, i32 0, i32 %36
  store i32 %35, i32* %38
  %39 = load i32, i32* %j
  %addtmpi22 = add i32 %39, 1
  store i32 %addtmpi22, i32* %j
  br label %forcond15

then:                                             ; preds = %forend12
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @5, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @4, i32 0, i32 0), i8 10)
  br label %ifend

else:                                             ; preds = %forend12
  store i32 0, i32* %i
  br label %forcond26

ifend:                                            ; preds = %forend50, %then
  ret i32 0

forcond26:                                        ; preds = %forend31, %else
  %40 = load i32, i32* %i
  %41 = load i32, i32* %M1
  %cmptmpi29 = icmp slt i32 %40, %41
  br i1 %cmptmpi29, label %forbody28, label %forend27

forend27:                                         ; preds = %forcond26
  store i32 0, i32* %i
  br label %forcond49

forbody28:                                        ; preds = %forcond26
  store i32 0, i32* %j
  br label %forcond30

forcond30:                                        ; preds = %forend35, %forbody28
  %42 = load i32, i32* %j
  %43 = load i32, i32* %N2
  %cmptmpi33 = icmp slt i32 %42, %43
  br i1 %cmptmpi33, label %forbody32, label %forend31

forend31:                                         ; preds = %forcond30
  %44 = load i32, i32* %i
  %addtmpi48 = add i32 %44, 1
  store i32 %addtmpi48, i32* %i
  br label %forcond26

forbody32:                                        ; preds = %forcond30
  store i32 0, i32* %z
  store i32 0, i32* %k
  br label %forcond34

forcond34:                                        ; preds = %forbody36, %forbody32
  %45 = load i32, i32* %k
  %46 = load i32, i32* %N1
  %cmptmpi37 = icmp slt i32 %45, %46
  br i1 %cmptmpi37, label %forbody36, label %forend35

forend35:                                         ; preds = %forcond34
  %47 = load i32, i32* %j
  %addtmpi47 = add i32 %47, 1
  store i32 %addtmpi47, i32* %j
  br label %forcond30

forbody36:                                        ; preds = %forcond34
  %48 = load i32, i32* %i
  %49 = load i32, i32* %N1
  %multmpi38 = mul i32 %48, %49
  %50 = load i32, i32* %k
  %addtmpi39 = add i32 %multmpi38, %50
  store i32 %addtmpi39, i32* %t
  %51 = load i32, i32* %t
  %52 = getelementptr [625 x i32], [625 x i32]* %A, i32 0, i32 %51
  %53 = load i32, i32* %52
  store i32 %53, i32* %x
  %54 = load i32, i32* %k
  %55 = load i32, i32* %N2
  %multmpi40 = mul i32 %54, %55
  %56 = load i32, i32* %j
  %addtmpi41 = add i32 %multmpi40, %56
  store i32 %addtmpi41, i32* %t
  %57 = load i32, i32* %t
  %58 = getelementptr [625 x i32], [625 x i32]* %B, i32 0, i32 %57
  %59 = load i32, i32* %58
  store i32 %59, i32* %y
  %60 = load i32, i32* %z
  %61 = load i32, i32* %x
  %62 = load i32, i32* %y
  %multmpi42 = mul i32 %61, %62
  %addtmpi43 = add i32 %60, %multmpi42
  store i32 %addtmpi43, i32* %z
  %63 = load i32, i32* %i
  %64 = load i32, i32* %N2
  %multmpi44 = mul i32 %63, %64
  %65 = load i32, i32* %j
  %addtmpi45 = add i32 %multmpi44, %65
  store i32 %addtmpi45, i32* %t
  %66 = load i32, i32* %z
  %67 = load i32, i32* %t
  %68 = load [625 x i32], [625 x i32]* %C
  %69 = getelementptr [625 x i32], [625 x i32]* %C, i32 0, i32 %67
  store i32 %66, i32* %69
  %70 = load i32, i32* %k
  %addtmpi46 = add i32 %70, 1
  store i32 %addtmpi46, i32* %k
  br label %forcond34

forcond49:                                        ; preds = %forend54, %forend27
  %71 = load i32, i32* %i
  %72 = load i32, i32* %M1
  %cmptmpi52 = icmp slt i32 %71, %72
  br i1 %cmptmpi52, label %forbody51, label %forend50

forend50:                                         ; preds = %forcond49
  br label %ifend

forbody51:                                        ; preds = %forcond49
  store i32 0, i32* %j
  br label %forcond53

forcond53:                                        ; preds = %forbody55, %forbody51
  %73 = load i32, i32* %j
  %74 = load i32, i32* %N2
  %cmptmpi56 = icmp slt i32 %73, %74
  br i1 %cmptmpi56, label %forbody55, label %forend54

forend54:                                         ; preds = %forcond53
  %printf61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @7, i32 0, i32 0), i8 10)
  %75 = load i32, i32* %i
  %addtmpi62 = add i32 %75, 1
  store i32 %addtmpi62, i32* %i
  br label %forcond49

forbody55:                                        ; preds = %forcond53
  %76 = load i32, i32* %i
  %77 = load i32, i32* %N2
  %multmpi57 = mul i32 %76, %77
  %78 = load i32, i32* %j
  %addtmpi58 = add i32 %multmpi57, %78
  store i32 %addtmpi58, i32* %t
  %79 = load i32, i32* %t
  %80 = getelementptr [625 x i32], [625 x i32]* %C, i32 0, i32 %79
  %81 = load i32, i32* %80
  %printf59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @6, i32 0, i32 0), i32 %81)
  %82 = load i32, i32* %j
  %addtmpi60 = add i32 %82, 1
  store i32 %addtmpi60, i32* %j
  br label %forcond53
}