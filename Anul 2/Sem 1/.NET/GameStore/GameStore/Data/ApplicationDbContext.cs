using GameStore.Models;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace GameStore.Data
{
    public class ApplicationDbContext : IdentityDbContext<ApplicationUser>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Item> Items { get; set; }

        public DbSet<Category> Categories { get; set; }

        public DbSet<Comment> Comments { get; set; }

        public DbSet<UserCategory> UserCategories { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            // definire primary key compus
            modelBuilder.Entity<UserCategory>()
            .HasKey(ab => new
            {
                ab.Id,
                ab.UserId,
                ab.CategoryId
            });
            // definire relatii cu modelele User si Category
            modelBuilder.Entity<UserCategory>()
            .HasOne(ab => ab.User)
            .WithMany(ab => ab.UserCategories)
            .HasForeignKey(ab => ab.UserId);

            modelBuilder.Entity<UserCategory>()
            .HasOne(ab => ab.Category)
            .WithMany(ab => ab.UserCategories)
            .HasForeignKey(ab => ab.CategoryId);
        }
    }
}