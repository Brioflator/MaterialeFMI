using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace GameStore.Models
{
    public class ApplicationUser : IdentityUser
    {

        [Required(ErrorMessage = "Please insert your First Name"), MaxLength(100)]
        public string FirstName { get; set; }
        [Required(ErrorMessage = "Please insert your Last Name"), MaxLength(100)]
        public string LastName { get; set; }
        public virtual ICollection<UserCategory>? UserCategories { get; set; }
        [NotMapped]
        public IEnumerable<SelectListItem>? AllRoles { get; set; }
        public virtual ICollection<Item>? Items { get; set; }
        public virtual ICollection<Comment>? Comments { get; set; }
        public virtual ICollection<Category>? Categories { get; set; }
    }
}
