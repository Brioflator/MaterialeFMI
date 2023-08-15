using Microsoft.AspNetCore.Mvc.Rendering;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace GameStore.Models
{
    public class Item
    {
        [Key]
        public int ItemId { get; set; }

        [Required(ErrorMessage = "Game name is required")]
        [StringLength(100, ErrorMessage = "Game name cannot be longer than 100 characters")]
        public string ItemTitle { get; set; }

        [Required(ErrorMessage = "Game description is required")]
        [DataType(DataType.MultilineText)]
        public string ItemDescription { get; set; }
        public int ItemPrice { get; set; }

        [Required(ErrorMessage = "Game category is required")]
        public int CategoryId { get; set; }

        [ForeignKey("CategoryId")]
        public virtual Category? Category { get; set; }

        public string ImagePath { get; set; }
        
        

        //should i keep this?
        public string? UserId { get; set; }
        public virtual ApplicationUser? User { get; set; }
        //

        public virtual ICollection<Comment>? Comments { get; set; }


    }
}
