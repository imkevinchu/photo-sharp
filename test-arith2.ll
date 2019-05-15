; ModuleID = 'MicroC'
source_filename = "MicroC"

@"Marie!" = global i32 0
@fmt = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@fmt.1 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@fmt.2 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @printbig(i32)

declare i32 @hello(i32)

declare i32 @printPix(i32*)

declare i32* @setPix(i32, i32, i32, i32)

declare i32* @open(i8*)

declare i32* @save(i8*, i32*)

declare i32 @PrintImage(i32*)

declare i32 @ImageContrast(i32*, i32)

declare i32 @ImageSaturate(i32*, i32)

declare i32 @ImageRotate90(i32*)

declare i32 @ImageAddNoise(i32*, double, double)

declare i32 @ImageKelvin(i32*, double)

declare i32 @ImageReflectY(i32*)

declare i32 @ImageReflectX(i32*)

declare i32 @ImageCrop(i32*, double)

declare i32 @ImageTint(i32*, i32)

declare i32 @ImageHSL(i32*, i32, i32, i32)

declare i32 @ImageSize(i32*)

declare i32 @ImageRevert(i32*)

declare i32* @getPixel(i32*, i32)

declare i32 @PixelSaturate(i32*, i32)

declare i32 @RedPixel(i32*)

declare i32* @newAlbum()

declare i32* @newImageGradient(i32*, i32)

declare i32* @GradToLayer(i32*, i32*)

declare i32* @GradContrast(i32*, i32)

declare i32* @GradHSL(i32*, i32, i32, i32)

declare i32 @addToAlbum(i32*, i32*)

declare i32 @AlbumSize(i32*)

declare i32* @GetImage(i32*, i32)

declare i32 @removeLast(i32*)

define i32 @main() {
entry:
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @fmt, i32 0, i32 0), i32 11)
  ret i32 0
}
