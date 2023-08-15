using System.ComponentModel.DataAnnotations.Schema;

namespace GameStore.Models
{
    public class UserCategory
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }

        public string? UserId { get; set; }
        public int? CategoryId { get; set; }
        public virtual ApplicationUser? User { get; set; }
        public virtual Category? Category { get; set; }
    }
}
