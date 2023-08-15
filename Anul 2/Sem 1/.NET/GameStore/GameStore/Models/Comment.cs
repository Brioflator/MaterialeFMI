using System.ComponentModel.DataAnnotations;

namespace GameStore.Models
{
    public class Comment
    {
        [Key]
        public int CommentId { get; set; }

        [Required(ErrorMessage = "Content is required")]
        [DataType(DataType.MultilineText)]
        public string? Content { get; set; }
        public DateTime Date { get; set; }
        public int? ItemId { get; set; }
        public virtual Item? Item { get; set; }

        public string? UserId { get; set; }
        public virtual ApplicationUser? User { get; set; }
    }
}
