using Microsoft.AspNetCore.Mvc;
using Comment = GameStore.Models.Comment;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Authorization;
using GameStore.Data;
using GameStore.Models;

namespace GameStore.Controllers
{
    public class CommentsController : Controller
    {
        private readonly ApplicationDbContext db;
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;

        public CommentsController(ApplicationDbContext context, UserManager<ApplicationUser> userManager, RoleManager<IdentityRole> roleManager)
        {
            db = context;
            _userManager = userManager;
            _roleManager = roleManager;
        }

        [HttpPost]
        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Delete(int id)
        {
            Comment comment = db.Comments.Find(id);
            if (comment.UserId == _userManager.GetUserId(User) || _roleManager.RoleExistsAsync("Admin").Result)
            {
                db.Comments.Remove(comment);
                db.SaveChanges();
                TempData["message"] = "Comment was deleted!";
                return Redirect("/Items/Show/" + comment.ItemId);
            }
            else
            {
                TempData["message"] = "You don't have the rights to delete this comment!";
                ViewBag.Message = TempData["message"];
                return Redirect("/Items/Show/" + comment.ItemId);
            }
            //return RedirectToAction("Index", "Items");
        }

    }
}
