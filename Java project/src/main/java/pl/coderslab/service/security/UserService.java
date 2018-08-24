package pl.coderslab.service.security;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.coderslab.entity.User;
import pl.coderslab.model.security.UserDto;
import pl.coderslab.repository.security.UserRepository;
import pl.coderslab.validation.security.EmailExistsException;

import javax.transaction.Transactional;
import java.util.Arrays;


@Service
public class UserService implements IUserService {
    @Autowired
    private UserRepository repository;

    @Transactional
    public User registerNewUserAccount(UserDto accountDto)
            throws EmailExistsException {

        if (emailExist(accountDto.getEmail())) {
            throw new EmailExistsException(
                    "There is an account with that email address: " + accountDto.getEmail());
        }
        User user = new User();
        user.setUsername(accountDto.getUsername());
        user.setPassword(accountDto.getPassword());
        user.setEmail(accountDto.getEmail());
        user.setRoles(Arrays.asList("ROLE_ADMIN"));
        return repository.save(user);
    }

    private boolean emailExist(String email) {
        User user = repository.findByEmail(email);
        if (user != null) {
            return true;
        }
        return false;
    }
}
