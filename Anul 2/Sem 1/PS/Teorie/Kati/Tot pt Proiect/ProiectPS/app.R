library(shiny)
library(shinyBS)
library(shinydashboard)
library(shinyjs)
library(shinyWidgets)
library(DT)
library(tidyverse)
library(ggthemes)
library(hrbrthemes)
library(plotly)
library(readxl)
library(writexl)
library(janitor)
library(plyr)
library(tidyquant)
library(lubridate)
library(toOrdinal)
library(scales)
library(xkcd)
library(lifecontingencies)

BrokenHeart_LifeTable <- function(widowed_status = FALSE, widowed_age = NULL, gender = 1){
  cnames <- read_excel("data/Broken Heart Life Table.xlsx", sheet = 1, n_max = 0) %>%
    names()
  
  if(gender == 1){
    life_table <- read_xlsx("data/Broken Heart Life Table.xlsx", sheet = 2, skip = 1, col_names = cnames) 
    band_1 = c(0.0295, 0.0321, 0.0223, 0.0163, 0.0226)
    band_2 = c(0.1221, 0.0146, 0.0653, 0.0351, 0.0000)
    band_3 = c(0.1954, 0.1713, 0.0688, 0.0806, 0.0000)
  } else {
    life_table <- read_xlsx("data/Broken Heart Life Table.xlsx", sheet = 1, skip = 1, col_names = cnames)
    band_1 = c(0.1835, 0.0695, 0.0254, 0.0556, 0.0000)
    band_2 = c(0.4699, 0.0923, 0.0461, 0.0000, 0.2322)
    band_3 = c(0.5097, 0.1452, 0.0888, 0.2150, 0.3785)
  }
  
  qx <- unlist(life_table[,2])
  
  if(widowed_status == TRUE){
    for(i in widowed_age:(widowed_age + 4))
      if(i <= 75){
        qx[i + 1] = band_1[i + 1 - widowed_age]
      } else if (76 <= i && i <= 85){
        qx[i + 1] = band_2[i + 1 - widowed_age]
      } else {
        if(i <= 95){
          qx[i + 1] = band_3[i + 1 - widowed_age]
        }
      }
  }
  
  broken_heart_lifetable <- probs2lifetable(probs = qx, radix = 11454, "qx", name = "broken_heart_lifetable")
  return(broken_heart_lifetable)
}

ui <- fluidPage(
  
  titlePanel("Broken Heart Effect"),
  
  sidebarLayout(
    
    sidebarPanel(
      
      radioButtons("bh_gender", "Gender parameters:",
                   c("Male" = 2, # 2
                     "Female" = 1)), #1
      
      br(),
      
      sliderInput("bh_age_current",
                  "Current age:",
                  value = 70,
                  min = 66,
                  max = 96),
      br(),
      sliderInput("bh_age_widowed",
                  "Age widowed:",
                  value = 70,
                  min = 66,
                  max = 96)
      
    ),
    
    
    mainPanel(
     
      useShinyjs(), #pt observe din server
      
      div(infoBox(title ="Widowed vs Not-Widowed Death Probabilites",  width = 32, icon = icon(""), plotlyOutput("bh_qx_change_plot"),hr())),
      hr(),
      div(infoBox(title ="Percentage Increase in Death Probabilites for Widowed Life", width = 32, icon = icon(""), plotlyOutput("bh_life_ex_change_plot"),hr())),
      
      box(title = "Life Expectancies", status = "primary", solidHeader = T, height = "270px",
          h4("Widowed:"),
          h3(textOutput("bh_text_life_ex_widowed")),
          hr(),
          h4("Not Widowed:"),
          h3(textOutput("bh_text_life_ex_not_widowed")),
      ),
      
      div(id = "bh_infobox_female", infoBox(
        title = "Difference in Life Expectancy for Female", h3(textOutput('bh_text_life_ex_diff_female')), width = 10,icon = icon(""))),
      
      div(id = "bh_infobox_male", infoBox(
        title = "Difference in Life Expectancy for Male", h3(textOutput('bh_text_life_ex_diff_male')), width = 10, icon = icon("")))
      
    )
  )
)

# Define server logic for random distribution app ----
server <- function(input, output) {
  
  # Reactive Functions -----------------------------------------------------
  bh_life_ex_widowed_reactive <- reactive({
    ex = exn(BrokenHeart_LifeTable(widowed_status = TRUE, widowed_age = input$bh_age_widowed, gender = input$bh_gender), input$bh_age_current)
    return(ex)
  })
  
  bh_life_ex_not_widowed_reactive <- reactive({
    ex = exn(BrokenHeart_LifeTable(widowed_status = FALSE, gender = input$bh_gender), input$bh_age_current)
    return(ex)
  })
  
  # Output Functions --------------------------------------------------------
  output$bh_text_life_ex_widowed <- renderText({
    return(c(round(bh_life_ex_widowed_reactive(), digits = 2), " Years"))
  })
  
  output$bh_text_life_ex_not_widowed <- renderText({
    return(c(round(bh_life_ex_not_widowed_reactive(), digits = 2), " Years"))
  })
  
  output$bh_text_life_ex_diff_female <- renderText({
    diff = bh_life_ex_not_widowed_reactive() - bh_life_ex_widowed_reactive()
    return(c(round(diff, digits = 2), " Years"))
  })
  
  output$bh_text_life_ex_diff_male <- renderText({
    diff = bh_life_ex_not_widowed_reactive() - bh_life_ex_widowed_reactive()
    return(c(round(diff, digits = 2), " Years"))
  })
  
  output$bh_qx_change_plot <- renderPlotly({
    bh_w_f = BrokenHeart_LifeTable(widowed_status = TRUE, widowed_age = input$bh_age_widowed, gender = 1)
    bh_no_f = BrokenHeart_LifeTable(widowed_status = FALSE, widowed_age = input$bh_age_widowed, gender = 1)
    bh_w_m = BrokenHeart_LifeTable(widowed_status = TRUE, widowed_age = input$bh_age_widowed, gender = 2)
    bh_no_m = BrokenHeart_LifeTable(widowed_status = FALSE, widowed_age = input$bh_age_widowed, gender = 2)
    bh_w_f_qx = bh_no_f_qx = bh_w_m_qx = bh_no_m_qx = numeric(getOmega(bh_w_f))
    
    for(i in 1:getOmega(bh_w_f) + 1){
      bh_w_f_qx[i] = (bh_w_f@lx[i] - bh_w_f@lx[i + 1])/bh_w_f@lx[i]
      bh_no_f_qx[i] = (bh_no_f@lx[i] - bh_no_f@lx[i + 1])/bh_no_f@lx[i]
      bh_w_m_qx[i] = (bh_w_m@lx[i] - bh_w_m@lx[i + 1])/bh_w_m@lx[i]
      bh_no_m_qx[i] = (bh_no_m@lx[i] - bh_no_m@lx[i + 1])/bh_no_m@lx[i]
    }
    
    df = data.frame(age = (input$bh_age_widowed - 1):(input$bh_age_widowed + 4), 
                    female_widowed = bh_w_f_qx[(input$bh_age_widowed):(input$bh_age_widowed + 5)],
                    female_not_widowed = bh_no_f_qx[(input$bh_age_widowed):(input$bh_age_widowed + 5)],
                    male_widowed = bh_w_m_qx[(input$bh_age_widowed):(input$bh_age_widowed + 5)],
                    male_not_widowed = bh_no_m_qx[(input$bh_age_widowed):(input$bh_age_widowed + 5)]
    )
    
    p <- ggplot(df, aes(x = age)) + xlab("Age") + ylab("Probability of Death (qx rate)") +
      geom_line(aes(y = female_widowed, colour = 'Female', linetype = 'Widowed', size = "Female")) + 
      geom_line(aes(y = female_not_widowed, colour = 'Female', linetype = 'Not Widowed', size = "Female")) + 
      geom_line(aes(y = male_widowed, colour = "Male", linetype = 'Widowed', size = "Male")) + 
      geom_line(aes(y = male_not_widowed, colour = "Male", linetype = "Not Widowed", size = "Male")) +
      
      scale_color_manual("Gender", values = c('#f112be', "#4A8DBF")) +
      scale_linetype_manual("Widowhood Status", values = c("Widowed" = 1, "Not Widowed" = 2)) +
      scale_size_manual("Gender", values = c(1, 1))
    
    ggplotly(p, tooltip = c("age", "female_widowed", "female_not_widowed", "male_widowed", "male_not_widowed")) 
  })
  
  output$bh_life_ex_change_plot <- renderPlotly({
    
    brokenheart_lifetable_widowed = BrokenHeart_LifeTable(widowed_status = TRUE, widowed_age = input$bh_age_widowed, gender = input$bh_gender)
    brokenheart_lifetable_not_widowed = BrokenHeart_LifeTable(widowed_status = FALSE, gender = input$bh_gender)
    bh_widowed_qx = bh_not_widowed_qx = numeric(getOmega(brokenheart_lifetable_widowed))
    
    for(i in 1:getOmega(brokenheart_lifetable_widowed) + 1)
    {
      bh_widowed_qx[i] = (brokenheart_lifetable_widowed@lx[i] - brokenheart_lifetable_widowed@lx[i + 1])/brokenheart_lifetable_widowed@lx[i]
      bh_not_widowed_qx[i] = (brokenheart_lifetable_not_widowed@lx[i] - brokenheart_lifetable_not_widowed@lx[i + 1])/brokenheart_lifetable_not_widowed@lx[i]
    }
    
    diff_qx = ((bh_widowed_qx - bh_not_widowed_qx) * 100)/bh_not_widowed_qx
    df = data.frame(age = input$bh_age_widowed:(input$bh_age_widowed + 4), diff_qx = diff_qx[(input$bh_age_widowed + 1):(input$bh_age_widowed + 5)])
    
    fig <- plot_ly(df, x = ~age, y = ~diff_qx, type = 'bar', color = if(input$bh_gender == 1){I('#f112be')}else{I('#4A8DBF')})
    fig <- fig %>% layout(xaxis = list(title = "Age"), yaxis = list(title = "% increase in qx rate"))
  
    })
  
  # Observe Event Functions -------------------------------------------------
  observeEvent(input$bh_gender,{
    if(input$bh_gender == 1) {
      shinyjs::hide("bh_infobox_male")
      shinyjs::show("bh_infobox_female")
    } 
    else {
      shinyjs::hide("bh_infobox_female")
      shinyjs::show("bh_infobox_male")
    }
  }
  )
  
}

# Create Shiny app ----
shinyApp(ui, server)