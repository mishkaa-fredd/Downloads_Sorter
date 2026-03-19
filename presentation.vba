Sub CreateDownloadsSorterPresentation()
    Dim pptApp As Object
    Dim pptPres As Object
    Dim slideIndex As Integer
    Dim currentSlide As Object
    
    Set pptPres = ActivePresentation
    slideIndex = 1

    ' Масив із заголовками та текстом
    Dim titles As Variant
    Dim content As Variant
    
    titles = Array("Downloads Sorter", "Проблема: Хаос у завантаженнях", "Наслідки безладу", _
                   "Наше рішення", "Як це працює?", "Демонстрація роботи", _
                   "Технічний стек", "Переваги автоматизації", "Майбутнє проекту", "Дякуємо за увагу!")
                   
    content = Array("Інтелектуальне сортування файлів", _
                    "Папка 'Завантаження' часто перетворюється на 'сміттєзвалище' документів, фото та інсталяторів.", _
                    "• Втрата часу на пошук файлів" & vbCrLf & "• Забита пам'ять" & vbCrLf & "• Ризик видалення важливих даних", _
                    "Downloads Sorter — скрипт, що миттєво розподіляє файли за категоріями (PDF, Images, Video, Executables).", _
                    "1. Сканування папки" & vbCrLf & "2. Визначення розширення" & vbCrLf & "3. Переміщення у відповідну підпапку", _
                    "Місце для відео (Screen Recording)", _
                    "• Python / Bash" & vbCrLf & "• FileSystem API" & vbCrLf & "• Гнучка конфігурація правил", _
                    "• Чистота 24/7" & vbCrLf & "• Жодної ручної роботи" & vbCrLf & "• Легке налаштування під себе", _
                    "• Хмарна синхронізація" & vbCrLf & "• AI-тегування контенту" & vbCrLf & "• Web-інтерфейс", _
                    "Будемо раді вашим запитанням!")

    For i = 0 To 9
        Set currentSlide = pptPres.Slides.Add(slideIndex, 12) ' 12 = ppLayoutBlank
        currentSlide.FollowMasterBackground = False
        currentSlide.Background.Fill.ForeColor.RGB = RGB(250, 250, 252) ' Світлий фон iOS
        
        ' Додавання логотипу (заповнювач)
        With currentSlide.Shapes.AddShape(1, 40, 30, 60, 60) ' 1 = msoShapeRectangle
            .Fill.ForeColor.RGB = RGB(0, 122, 255) ' iOS Blue
            .Line.Visible = False
            .TextFrame.TextRange.Text = "LOGO"
            .TextFrame.TextRange.Font.Size = 10
        End With
        
        ' Заголовок
        With currentSlide.Shapes.AddTextbox(1, 50, 100, 620, 50)
            .TextFrame.TextRange.Text = titles(i)
            .TextFrame.TextRange.Font.Name = "SF Pro Display" ' Шрифт iOS
            .TextFrame.TextRange.Font.Size = 36
            .TextFrame.TextRange.Font.Bold = True
            .TextFrame.TextRange.Font.Color.RGB = RGB(20, 20, 20)
        End With
        
        ' Основний контент
        With currentSlide.Shapes.AddTextbox(1, 50, 180, 62)
