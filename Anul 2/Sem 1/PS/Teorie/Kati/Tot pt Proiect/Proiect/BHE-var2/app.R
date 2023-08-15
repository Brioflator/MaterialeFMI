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
options(scipen=999)

# Broken Heart Life Table -------------------------------------------------
BrokenHeart_LifeTable <- function(widowed_status = FALSE, widowed_age = NULL, gender = 1){
  cnames <- read_excel("data/Broken Heart Life Table.xlsx", sheet = 1, n_max = 0) %>%
    names()
  
  if(gender == 1){
    life_table <- read_xlsx("data/Broken Heart Life Table.xlsx", sheet = 2, skip = 1, col_names = cnames) %>% 
      drop_na()
    band_1 = c(0.0295, 0.0321, 0.0223, 0.0163, 0.0226)
    band_2 = c(0.1221, 0.0146, 0.0653, 0.0351, 0.0000)
    band_3 = c(0.1954, 0.1713, 0.0688, 0.0806, 0.0000)
  } else {
    life_table <- read_xlsx("data/Broken Heart Life Table.xlsx", sheet = 1, skip = 1, col_names = cnames) %>% 
      drop_na()
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


# Plotly - Horizontal & Vertical Lines ------------------------------------
plotly_hline <- function(y = 0, colour = "blue") {
  list(type = "line", x0 = 0, x1 = 1, xref = "paper", y0 = y, y1 = y, line = list(color = colour, width = 3, dash = 'dash'))
}

plotly_vline <- function(x = 0, colour = "red") {
  list(type = "line", y0 = 0, y1 = 1, yref = "paper", x0 = x, x1 = x, line = list(color = colour, width = 3, dash = 'dash'))
}

# General UI --------------------------------------------------------------
ui <- dashboardPage(
  dashboardHeader(title = "Actuarial Tasks in R",
                  dropdownMenu(
                    type = "notifications", 
                    headerText = strong("See the code behind the app:"), 
                    icon = icon("code"), 
                    badgeStatus = NULL,
                    notificationItem(
                      text = "Click here to visit the GitHub Page",
                      href = "https://github.com/Jimzo123/FYP_MS4090",
                      icon = icon("github")
                    ),
                    tags$li(
                      actionLink("Disclaimer", "DISCLAIMER", class = "my_class"),
                      icon = icon("info"),
                      class = "dropdown"
                    )
                  )
  ),
  
  dashboardSidebar(
    # collapsed = T,
    sidebarMenu(id = 'tabs',
                menuItem("Broken Heart Effect", tabName = "broken_heart", icon = icon("heart-broken"))
    )
  ),
  
  dashboardBody(
    tags$style(".well {background-color:white; border-color:#3C8DBC; margin-left:1em;}
                   .nav-tabs-custom {border: 1px solid #3C8DBC}
                   .box {border: 1px solid #3C8DBC}"),
    useShinyjs(),
    fluidRow(
      tabItems(
        tabItem(tabName = 'broken_heart', source("source_scripts/ui.R", local = TRUE)[1])
        )
    )
  )
)

# General Server ----------------------------------------------------------
server <- function(input, output, session) {
  source("source_scripts/server.R", local = TRUE)[1]
  
  observeEvent(input$Disclaimer, {
    showModal(modalDialog(
      title = "Important Message",
      "This application is for demonstration purposes only. While this application has been developed with all due care,
        we do not warrant or represent that it is free from errors or omission."
    ))
  })
}

# Run the application 
shinyApp(ui = ui, server = server)