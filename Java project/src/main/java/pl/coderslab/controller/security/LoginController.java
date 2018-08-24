package pl.coderslab.controller.security;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import pl.coderslab.entity.User;
import pl.coderslab.model.security.UserDto;
import pl.coderslab.service.security.IUserService;
import pl.coderslab.validation.security.EmailExistsException;

import javax.validation.Valid;


@Controller
public class LoginController {
    @Autowired
    IUserService userService;

    @GetMapping("/login")
    public ModelAndView login() {
        ModelAndView model = new ModelAndView();
        model.setViewName("security/login");
        return model;
    }

    @GetMapping("/register")
    public String register(WebRequest request, Model model) {
        UserDto userDto = new UserDto();
        model.addAttribute("user", userDto);
        return "security/register";
    }

    @PostMapping("/register")
    public String registerUserAccount(@ModelAttribute("user") @Valid UserDto accountDto, BindingResult result,
                                      WebRequest request, Errors errors, RedirectAttributes redirectAttributes) {
        User registered = new User();
        if (!result.hasErrors()) {
            registered = createUserAccount(accountDto, result);
        }
        if (registered == null) {
            result.rejectValue("email", "message.regError");
        }
        if (result.hasErrors()) {
            return "security/register";
        } else {
            redirectAttributes.addFlashAttribute("msg", "Registration successful!");
            return "redirect:/";
        }
    }

    private User createUserAccount(UserDto accountDto, BindingResult result) {
        User registered = null;
        try {
            registered = userService.registerNewUserAccount(accountDto);
        } catch (EmailExistsException e) {
            return null;
        }
        return registered;
    }
}
