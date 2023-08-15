using System.ComponentModel.DataAnnotations;

namespace GameStore.Models
{
    public class Category
    {
        [Key]
        public int CategoryId { get; set; }


        [Required(ErrorMessage = "Category name is required")]
        [StringLength(20, ErrorMessage = "Name can't be longer than 20 characters")]
        public string CategoryName { get; set; }
        public string CategoryDescription { get; set; }

        public string? UserId { get; set; }
        public virtual ApplicationUser? User { get; set; }

        public virtual ICollection<Item>? Items { get; set; }
        public virtual ICollection<UserCategory>? UserCategories { get; set; }

    }
}
